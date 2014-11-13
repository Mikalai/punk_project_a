#include <iostream>
#include <QtCore/qtimezone.h>
#include <QtWidgets/qgraphicsitem.h>
#include <stack>
#include <deque>
#include <chrono>
#include <QtWidgets/qgraphicssceneevent.h>
#include <QtWidgets/qgraphicsview.h>
#include <QtGui/qpainter.h>
#include "resources.h"
#include "global_field.h"
#include "global_field_cell.h"
#include "squad.h"
#include "city.h"
#include "city_graphics_item.h"
#include "squad_graphics_item.h"
#include "road.h"
#include "Character.h"
#include "buildings.h"
#include "weather.h"

static const int CELL_SIZE = 64;

class GlobalFieldCellItem : public QGraphicsItem {
public:

	enum { Type = QGraphicsItem::UserType + (int)ModelType::GlobalFieldCell };

	GlobalFieldCellItem(GlobalFieldCell* cell, GlobalField* field)
		: m_cell{ cell }
		, m_field{ field } {

		QMatrix m{};
		m.translate(m_cell->position.x()*CELL_SIZE, m_cell->position.y()*CELL_SIZE);
		setTransform(QTransform(m));
		setZValue(0.0f);
	}

	QRectF boundingRect() const override {
		return QRectF(-CELL_SIZE / 2, -CELL_SIZE / 2, CELL_SIZE, CELL_SIZE);
	}

	QBrush GetGroundBrush() {
		return QBrush{ *Resources::instance()->getImage(m_cell->ground) };
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		auto brush = GetGroundBrush();
		auto pen = painter->pen();
		pen.setStyle(Qt::PenStyle::NoPen);
		painter->setPen(pen);
		painter->setBrush(brush);
		painter->drawRect(-CELL_SIZE / 2, -CELL_SIZE / 2, CELL_SIZE, CELL_SIZE);
		painter->drawText(QPointF{ 0, 0 }, QString::number(m_cell->findPath(m_field->getTlsIndex())->full_path_cost));
	}

	GlobalFieldCell* cell() const {
		return m_cell;
	}

	int type() const override {
		return Type;
	}

private:
	GlobalFieldCell* m_cell{ nullptr };
	GlobalField* m_field{ nullptr };
};


GlobalField::GlobalField(QObject* parent)
	: QGraphicsScene{ parent }
{
	connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));

	m_path_finder_thread = std::thread(pathFinderFunc, this);
	allocateTls(std::this_thread::get_id());
	allocateTls(m_path_finder_thread.get_id());
}

GlobalField::~GlobalField() {
	while (!m_squads.empty()){
		delete m_squads.back();
		m_squads.pop_back();
	}

	while (!m_cities.empty()) {
		delete m_cities.back();
		m_cities.pop_back();
	}

	while (!m_roads.empty()) {
		delete *m_roads.begin();
		m_roads.erase(m_roads.begin());
	}

	while (!m_building.empty()) {
		delete m_building.back();
		m_building.pop_back();
	}
}

void GlobalField::pathFinderFunc(GlobalField* _this) {
	GlobalField* field = _this;

	while (!field->m_terminate) {
		std::unique_lock<std::mutex> lock{ field->m_path_find_mutex };
		auto tasks = field->m_path_find_tasks;
		//qDebug("Recieved %d tasls", tasks.size());
		field->m_path_find_tasks.clear();
		lock.unlock();
		while (!tasks.empty()) {
			auto task = tasks.back();
			//qDebug("Find path task recieved from %d;%d to %d;%d", task->start.x(), task->start.y(), task->end.x(), task->end.y());
			tasks.pop_back();
			task->has_path = field->getPath(task->start, task->end, task->path);
			task->has_result = true;
		}


		lock.lock();
		field->m_path_find_cond.wait(lock, [&field]() {

			//	if terminate request - stop waiting
			if (field->m_terminate)
				return true;
			//if (field->m_path_find_tasks.empty())
			//qDebug("Wait till new find path tasks");
			return !field->m_path_find_tasks.empty();
		});
	}
}

void GlobalField::Create() {
	Create(0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, true, 5);
}

void GlobalField::Create(float grass, float water, float sand, float dirt, float forest, float rocks, bool island, int sea_width) {
	clear();
	m_cells.resize(m_width*m_height);

	m_current_time = QDateTime(QDate(2012, 7, 6), QTime(21, 30, 0));

	//	allocate TLS
	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			m_cells[y*m_width + x].setTlsCount(2);
		}
	}

	//	normalize weights
	float sum = 0;
	sum = grass + water + sand + dirt + forest + rocks;
	grass /= sum;
	water /= sum;
	sand /= sum;
	dirt /= sum;
	forest /= sum;
	rocks /= sum;
	water = water + grass;
	sand = sand + water;
	dirt = dirt + sand;
	forest = forest + dirt;
	rocks = rocks + forest;

	qDebug("Global field cell distribution: grass %f; water %f; sand %f; dirt %f; forest %f; rocks %f", grass, water, sand, dirt, forest, rocks);

	//	generate
	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			auto cell = &m_cells[y*m_width + x];

			// store position
			cell->position = QPoint{ x, y };

			//	store ground
			float rnd = rand() / (float)RAND_MAX;
			if (rnd < grass)
				cell->ground = SurfaceType::Grass;
			else if (rnd < water)
				cell->ground = SurfaceType::Water;
			else if (rnd < sand)
				cell->ground = SurfaceType::Sand;
			else if (rnd < dirt)
				cell->ground = SurfaceType::Dirt;
			else if (rnd < forest)
				cell->ground = SurfaceType::Forest;
			else if (rnd < rocks)
				cell->ground = SurfaceType::Rocks;

			//	if island make water on the edge of the map
			if (island) {
				if (y <= sea_width)
					cell->ground = SurfaceType::Water;
				if (y >= m_height - sea_width)
					cell->ground = SurfaceType::Water;
				if (x <= sea_width)
					cell->ground = SurfaceType::Water;
				if (x >= m_width - sea_width)
					cell->ground = SurfaceType::Water;
			}

			GlobalFieldCellItem* item = new GlobalFieldCellItem{ cell, this };
			addItem(item);
		}
	}

	//	create player squad
	Squad* s = new Squad(new Character{ this, this }, this, this);
	s->setHumanControl(true);
	s->setPosition(6, 6);
	addSquad(s);

	auto& list = QGraphicsScene::views();
	for (auto view : list) {
		view->centerOn(s->model());
	}

	//	create cities
	for (int i = 0; i < m_max_city_count; ++i) {
		City* c = new City{ this, this };
		if (i == 0) {
			c->setPosition(10, 10);
			c->setHumanControl(true);
		}
		else {
			c->setPosition(rand() % m_width, rand() % m_height);
		}
		addCity(c);
	}

	m_cities[0]->buildRoad(cell(m_cities[0]->position()), cell(m_cities[1]->position()));
}

void GlobalField::updateByTimer() {
	TimeDependent::update();
	auto dt = getTimeStep();
	static float t = 0;
	t += dt;
	if (t >= 1.0f) {
		m_current_time = m_current_time.addSecs(t);
		auto w = Temperature::instance()->weather(m_current_time);
		emit weatherChanged(w);
		t = 0;
		emit timeChanged(m_current_time);
	}
	//std::cout << dt * 1000.0f << std::endl;
	//qDebug(__FUNCTION__);

	// clear trash
	while (!m_entities_to_delete.empty()) {
		delete m_entities_to_delete.back();
		m_entities_to_delete.pop_back();
	}

	//	create squads if not enough
	if (m_squads.size() < m_max_squad_count) {
		Squad* s = new Squad(new Character{ this, this }, this, this);
		s->setHumanControl(false);
		s->setPosition(50, 50);
		addSquad(s);
	}

	//	update cells
	if (m_last_row_update >= m_height) {
		m_last_row_update = 0;
	}

	for (int x = 0; x < m_width; ++x) {
		m_cells[m_last_row_update*m_width + x].update();
	}
	m_last_row_update++;

	//	update squads
	for (auto& squad : m_squads) {
		squad->update();
	}

	//	update cities
	for (auto& city : m_cities) {
		city->update();
	}

	//	update buildings
	for (auto& building : m_building) {
		building->update();
	}
}

float GlobalField::cellSize() {
	return CELL_SIZE;
}

void GlobalField::addSquad(Squad* value) {
	auto it = std::find(m_squads.begin(), m_squads.end(), value);
	if (it != m_squads.end())
		return;
	m_squads.push_back(value);
	addItem(value->model());
}

void GlobalField::addCity(City* city) {
	auto it = std::find(m_cities.begin(), m_cities.end(), city);
	if (it != m_cities.end())
		return;
	m_cities.push_back(city);
	addItem(city->model());
}

void GlobalField::onSelectionChanged() {
	qDebug(__FUNCTION__);
	auto& items = selectedItems();

	//	drop selection
	if (items.empty()) {
		emit selectionDropped();
	}

	m_selected_squads.clear();
	for (auto item : items) {

		//	check if squads were selected
		SquadGraphicsItem* squad_item = qgraphicsitem_cast<SquadGraphicsItem*>(item);
		if (squad_item) {
			qDebug("Squad selected");
			if (squad_item->getSquad()->isHumanControl()) {
				m_selected_squads.insert(squad_item->getSquad());
				emit citySelected(nullptr);
			}
		}

		// check if city was selected
		CityGraphicsItem* city_item = qgraphicsitem_cast<CityGraphicsItem*>(item);
		if (city_item) {
			qDebug("City selected");
			if (city_item->getCity()->isHumanControl()) {
				emit citySelected(city_item->getCity());
				break;
			}
		}
	}
}

void GlobalField::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) {

	auto all_items = items(mouseEvent->scenePos());
	for (auto& item : all_items) {
		auto field_cell_item = qgraphicsitem_cast<GlobalFieldCellItem*>(item);
		if (field_cell_item)
			emit fieldCellPressed(mouseEvent, field_cell_item->cell());
	}	

	//if (m_mode == InteractionMode::Select) {
		if (mouseEvent->button() == Qt::RightButton && !m_squads.empty()) {
			for (auto& item : all_items) {
				auto field_cell_item = qgraphicsitem_cast<GlobalFieldCellItem*>(item);
				if (field_cell_item) {
					auto cell = field_cell_item->cell();
					for (auto squad : m_selected_squads) {
						if (squad->isHumanControl())
							squad->goTo(cell);
					}
				}
			}
		}
		else {
			QGraphicsScene::mousePressEvent(mouseEvent);
		}
	//}
	//else if (m_mode == InteractionMode::BuildRoad) {

	//}	
}

float GlobalField::timeStep() {
	return 0.01;
}


bool GlobalField::findPath(const QPoint& start, const QPoint& end, std::list<GlobalFieldCell*>& cells) {
	//qDebug("Search for path from %d;%d to %d;%d", start.x(), start.y(), end.x(), end.y());

	if (start == end)
		return false;

	auto tls_index = getTlsIndex();

	getTls(tls_index)->find_path_magic++;
	auto start_cell = cell(start);
	std::deque<GlobalFieldCell*> stack;
	stack.push_back(start_cell);

	GlobalFieldCell* end_cell = nullptr;
	while (!stack.empty()) {
		auto cell = stack.front();
		stack.pop_front();
		//qDebug("Process cell %d;%d", cell->position.x(), cell->position.y());
		if (cell->position == end) {
			end_cell = cell;
			break;
		}

		for (int y = -1; y < 2; ++y) {
			for (int x = -1; x < 2; ++x) {
				if (x == 0 && y == 0)
					continue;
				auto next_cell = this->cell(cell->position.x() + x, cell->position.y() + y);
				if (next_cell) {
					if (next_cell->findPath(tls_index)->find_path_magic != getTls(tls_index)->find_path_magic) {
						next_cell->findPath(tls_index)->find_path_number = cell->findPath(tls_index)->find_path_number + 1;
						next_cell->findPath(tls_index)->find_path_magic = getTls(tls_index)->find_path_magic;
						stack.push_back(next_cell);
					}
				}
			}
		}
	}

	QGraphicsScene::update();

	cells.clear();
	if (end_cell) {
		cells.push_front(end_cell);
		while (end_cell != start_cell) {
			GlobalFieldCell* cell = nullptr;
			for (int y = -1; y < 2; ++y) {
				for (int x = -1; x < 2; ++x) {
					auto temp = this->cell(end_cell->position.x() + x, end_cell->position.y() + y);
					if (!cell)
						cell = temp;
					int diff_old = end_cell->findPath(tls_index)->find_path_number - cell->findPath(tls_index)->find_path_number;
					int diff_new = temp->findPath(tls_index)->find_path_number - cell->findPath(tls_index)->find_path_number;
					if (diff_new < diff_old)
						if (cell && cell->findPath(tls_index)->find_path_magic == getTls(tls_index)->find_path_magic && cell->findPath(tls_index)->find_path_number == end_cell->findPath(tls_index)->find_path_number - 1) {
						end_cell = cell;
						cells.push_front(end_cell);
						goto next_cell;
						}
				}
			}
		next_cell:
			;
		}

		//qDebug("Path found");
		for (auto cell : cells) {
			//qDebug("Cell %d %d", cell->position.x(), cell->position.y());
		}
		return true;
	}
	else {
		//qDebug("Cell not found");
		return false;
	}
}

GlobalFieldCell* GlobalField::cell(const QPoint& value) {
	if (value.x() < 0 || value.x() >= m_width)
		return nullptr;
	if (value.y() < 0 || value.y() >= m_height)
		return nullptr;
	return &m_cells[value.y() * m_width + value.x()];
}

void addOpenSet(std::vector<GlobalFieldCell*>& cells, GlobalFieldCell* cell, int tls_index) {
	auto index = cells.size();
	cells.push_back(cell);
	cell->findPath(tls_index)->opened = index;
}

void eraseOpenSet(std::vector<GlobalFieldCell*>& cells, GlobalFieldCell* cell, int tls_index) {
	auto index = cell->findPath(tls_index)->opened;
	std::swap(cells.back(), cells.at(index));
	cells.at(index)->findPath(tls_index)->opened = index;
	cells.pop_back();
}

bool GlobalField::findPathA(GlobalFieldCell* start, GlobalFieldCell* end, std::list<GlobalFieldCell*>& cells) {
	if (start == nullptr || end == nullptr)
		return false;

	auto tls_index = getTlsIndex();
	std::vector<GlobalFieldCell*> neighbours;
	neighbours.reserve(8);

	getTls(tls_index)->find_path_magic++;
	//std::set<GlobalFieldCell*> closed;
	std::vector<GlobalFieldCell*> openset;
	openset.reserve(m_width);
	addOpenSet(openset, start, tls_index);
	//start->findPath(tls_index)->opened = true;
	start->findPath(tls_index)->find_path_magic = getTls(tls_index)->find_path_magic;
	start->findPath(tls_index)->find_path_cost = 0;
	start->findPath(tls_index)->find_path_heuristic_const = heuristicCost(start, end);
	start->findPath(tls_index)->full_path_cost = start->findPath(tls_index)->find_path_cost + start->findPath(tls_index)->find_path_heuristic_const;
	start->findPath(tls_index)->source = nullptr;

	while (!openset.empty()) {
		auto cell = minimalFullCost(openset, tls_index);
		if (cell == end) {
			return reconstructPath(start, end, cells, tls_index);
		}

		eraseOpenSet(openset, cell, tls_index);

		cell->findPath(tls_index)->closed = true;	// closed.insert(cell);

		neighbours.clear();
		neighbourCells(cell, neighbours);

		for (auto& neighbour : neighbours) {
			//	clear results from any other search
			if (neighbour->findPath(tls_index)->find_path_magic != getTls(tls_index)->find_path_magic) {
				auto data = neighbour->findPath(tls_index);
				data->find_path_magic = getTls(tls_index)->find_path_magic;
				data->source = nullptr;
				data->find_path_heuristic_const = 0;
				data->full_path_cost = 0;
				data->find_path_cost = 0;
				data->closed = false;
				data->opened = -1;
			}

			//if (closed.find(neighbour) != closed.end())
			if (neighbour->findPath(tls_index)->closed)
				continue;

			float tentative_g_score = cell->findPath(tls_index)->find_path_cost + distanceCost(cell, neighbour);
			bool tentative_is_better = false;

			if (neighbour->findPath(tls_index)->opened == -1) {
				addOpenSet(openset, neighbour, tls_index);
				tentative_is_better = true;
			}
			else {
				if (tentative_g_score < neighbour->findPath(tls_index)->find_path_cost) {
					tentative_is_better = true;
				}
				else {
					tentative_is_better = false;
				}
			}

			if (tentative_is_better) {
				neighbour->findPath(tls_index)->source = cell;
				neighbour->findPath(tls_index)->find_path_cost = tentative_g_score;
				neighbour->findPath(tls_index)->find_path_heuristic_const = heuristicCost(neighbour, end);
				neighbour->findPath(tls_index)->full_path_cost = neighbour->findPath(tls_index)->find_path_cost + neighbour->findPath(tls_index)->find_path_heuristic_const;
			}
		}
	}
	return false;
}

float GlobalField::heuristicCost(GlobalFieldCell* cell, GlobalFieldCell* end) {
	return (cell->position - end->position).manhattanLength();
}

void GlobalField::neighbourCells(GlobalFieldCell* cell, std::vector<GlobalFieldCell*>& cells) {
	for (int y = -1; y < 2; ++y) {
		for (int x = -1; x < 2; ++x) {
			if (x == 0 && y == 0)
				continue;
			auto c = this->cell(cell->position.x() + x, cell->position.y() + y);
			if (c) {
				cells.push_back(c);
			}
		}
	}
}

float GlobalField::distanceCost(GlobalFieldCell* start, GlobalFieldCell* end) {
	return (start->position - end->position).manhattanLength() * end->getBaseMoveDifficulty();
}

bool GlobalField::reconstructPath(GlobalFieldCell* start, GlobalFieldCell* end, std::list<GlobalFieldCell*>& cells, int tls_index) {
	auto current = end;
	cells.clear();

	while (current) {
		cells.push_front(current);
		current = current->findPath(tls_index)->source;
	}
	//cells.pop_front();
	return true;
}

GlobalFieldCell* GlobalField::minimalFullCost(std::vector<GlobalFieldCell*>& cells, int tls_index) {
	if (cells.empty())
		return nullptr;

	auto min = cells.front();
	for (auto& c : cells) {
		if (min->findPath(tls_index)->full_path_cost > c->findPath(tls_index)->full_path_cost)
			min = c;
	}
	return min;
}

bool GlobalField::getPath(const QPoint& start, const QPoint& end, std::list<GlobalFieldCell*>& path) {
	auto s = std::chrono::high_resolution_clock::now();
	auto result = findPathA(cell(start), cell(end), path);
	auto e = std::chrono::high_resolution_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::microseconds>(e - s).count() / (float)1000000.0f;
	//qDebug("Path calculation took %f s", diff);
	return result;
}

FindPathResult* GlobalField::beginGetPath(const QPoint& start, const QPoint& end) {
	//qDebug(__FUNCTION__);
	auto it = std::find_if(m_path_find_result.begin(), m_path_find_result.end(), [](const FindPathResult& r) {
		return !r.is_used || (r.is_canceled && r.has_result);
	});

	FindPathResult* result = nullptr;
	if (it != m_path_find_result.end())
		result = &(*it);
	else {
		FindPathResult new_result;
		m_path_find_result.push_back(new_result);
		result = &m_path_find_result.back();
	}

	result->path.clear();
	result->has_path = false;
	result->has_result = false;
	result->is_used = true;
	result->is_canceled = false;
	result->start = start;
	result->end = end;

	std::unique_lock<std::mutex> lock{ m_path_find_mutex };
	m_path_find_tasks.push_back(result);
	lock.unlock();
	m_path_find_cond.notify_all();

	return result;
}

void GlobalField::endGetPath(FindPathResult* result) {
	result->path.clear();
	result->is_used = false;
	result->has_path = false;
	result->has_result = false;
	QGraphicsScene::update();
}

void GlobalField::cancelGetPath(FindPathResult* result) {
	result->is_canceled = true;
}

void GlobalField::terminate() {
	m_terminate = true;
	m_path_find_cond.notify_all();
	m_path_finder_thread.join();
}

void GlobalField::addRoad(Road* road) {
	if (!road)
		return;

	auto it = m_roads.find(road);
	if (it != m_roads.end()) {
		qDebug("Road has been already added to the scene");
		return;
	}

	m_roads.insert(road);
	addItem(road->model());
}

void GlobalField::removeRoad(Road* road) {
	if (!road)
		return;

	auto it = m_roads.find(road);
	if (it == m_roads.end()) {
		qDebug("Can't remove road from the field because it was not added");
		return;
	}
	road->removeRoad();
	m_roads.erase(road);
	removeItem(road->model());
}

void GlobalField::setInteractionMode(GlobalField::InteractionMode value) {
	m_mode = value;
}

void GlobalField::addBuilding(Construction* value) {
	if (!value)
		return;

	auto it = std::find(m_building.begin(), m_building.end(), value);
	if (it != m_building.end()) {
		qDebug("Can't add building. Already added");
		return;
	}
	m_building.push_back(value);
	addItem(value->model());
}

void GlobalField::removeBuilding(Construction* value) {
	if (!value)
		return;

	auto it = std::find(m_building.begin(), m_building.end(), value);
	if (it == m_building.end()) {
		qDebug("Can't remove building. Not added");
		return;
	}
	m_building.erase(it);
}

void GlobalField::removeSquad(Squad* value) {
	if (!value)
		return;

	auto it = std::find(m_squads.begin(), m_squads.end(), value);
	if (it == m_squads.end()) {
		qDebug("Can't remove squad from field. Not added");
		return;
	}
	removeItem(value->model());
	m_squads.erase(it);
}

void GlobalField::removeCity(City* value) {
	if (!value)
		return;

	auto it = std::find(m_cities.begin(), m_cities.end(), value);
	if (it == m_cities.end()) {
		qDebug("Can't remove city from field. Not added.");
		return;
	}
	removeItem(value->model());
	m_cities.erase(it);
}

void addSquad(GlobalField* field, Squad* squad) {
	if (!field || !squad)
		return;

	field->addSquad(squad);
	
	GlobalFieldCell* cell = field->cell(squad->position());
	cell->addEntity(squad);
}

void removeSquad(GlobalField* field, Squad* squad) {
	if (!field || !squad)
		return;

	field->removeSquad(squad);
	field->moveToTrash(squad);

	auto cell = field->cell(squad->position());
	cell->removeEntity(squad);
}

void addCity(GlobalField* field, City* value) {
	if (!field || !value)
		return;

	field->addCity(value);

	GlobalFieldCell* cell = field->cell(value->position());
	cell->addEntity(value);
}

void removeCity(GlobalField* field, City* city) {
	if (!field || !city)
		return;

	//	all the Characters in the city became independent squads
	auto characters = city->characters();
	for (auto& character : characters) {
		addSquad(field, new Squad{ character, field, field });
	}

	field->removeCity(city);
	field->moveToTrash(city);

	auto cell = field->cell(city->position());
	cell->removeEntity(city);
}

void addBuilding(GlobalField* field, Construction* construction) {
	if (!field || !construction)
		return;

	field->addBuilding(construction);

	GlobalFieldCell* cell = field->cell(construction->position());
	cell->addEntity(construction);
}

void removeBuilding(GlobalField* field, Construction* construction) {
	if (!field || !construction)
		return;

	field->removeBuilding(construction);
	field->moveToTrash(construction);

	auto cell = field->cell(construction->position());
	cell->removeEntity(construction);
}

void addRoad(GlobalField* field, Road* road) {
	if (!field || !road)
		return;

	field->addRoad(road);

	auto& path = road->getPath();
	for (auto& cell : path) {
		cell->addRoad(road);
	}
}

void removeRoad(GlobalField* field, Road* road) {
	if (!field || !road)
		return;

	field->removeRoad(road);

	auto& path = road->getPath();

	for (auto& cell : path) {
		cell->removeRoad(road);
	}
}

Entity* GlobalField::player() {
	for (auto& s : m_squads) {
		if (s->isHumanControl())
			return s;
	}
	return nullptr;
}