#include <QtCore/qdebug.h>
#include <iostream>
#include <QtCore/qpoint.h>
#include <QtWidgets/qgraphicsview.h>
#include <QtGui/qevent.h>
#include <QtCore/qfile.h>
#include <QtWidgets/qgraphicssceneevent.h>
#include <QtCore/qdir.h>
#include <QtCore/qstandardpaths.h>
#include <QtGui/qpainter.h>
#include <fstream>
#include <QtWidgets/qgraphicsitem.h>
#include "local_field.h"
#include "global_field.h"
#include "global_field_cell.h"
#include "resources.h"
#include "keys.h"
#include "unit.h"
#include "unit_item.h"
#include "character.h"
#include "items.h"
#include "world.h"
#include "local_field_cell.h"
#include "options.h"

void destroy(LocalField* value) {
	delete value;
}

void destroy(LocalFieldCell* value) {
	delete value;
}


LocalField::LocalField(GlobalField* field, GlobalFieldCell* cell, QObject* parent)
	: Field{ field->world(), parent }
	, m_global_field{ field }
	, m_global_field_cell{ cell }
{}

LocalField::~LocalField() {
}

void LocalField::create(int width, int height) {
	m_width = width;
	m_height = height;

	auto global_pos = globalCell()->pos();
	//m_cells.resize(m_width*m_height);
	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			QPointF pos{ x*cellSize(), y*cellSize() };
			auto cell = make_ptr(new LocalFieldCell{ global_pos + pos, nullptr });
			addItem(cell.get());
			m_cells.push_back(std::move(cell));
		}
	}

	//	create temporary unit
	//Unit* unit = new Unit{ m_owner, new Character{ m_owner->field(), m_owner }, 1, m_owner };
	//unit->character()->setHumanControl(true);
	////unit->setPosition(QPointF{ 1, 1 });
	//addUnit(unit);

	//for (auto view : m_owner->views()) {
	//	view->setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorViewCenter);
	//	view->scale(1, 1);
	//	view->centerOn(unit->model());
	//}
}

//void addUnit(Unit* unit) {
//	auto it = std::find(m_units.begin(), m_units.end(), unit);
//	if (it != m_units.end()) {
//		qDebug("Can't add unit. Already added");
//		return;
//	}
//	if (unit->isHumanControl()) {
//		m_human_unit = unit;
//	}
//	m_units.push_back(unit);
//	m_owner->addItem(unit->model());
//}
//
//void removeUnit(Unit* unit) {
//	auto it = std::find(m_units.begin(), m_units.end(), unit);
//	if (it == m_units.end()) {
//		qDebug("Can't remove unit from local field. not added");
//		return;
//	}
//	m_units.erase(it);
//	m_owner->removeItem(unit->model());
//}

void LocalField::update() {
	Field::update();
	auto dt = getTimeStep();

	/*for (auto unit : m_units) {
		unit->update();
	}*/

	auto children = items();
	for (auto item : children) {
		LocalFieldCell* cell = qgraphicsitem_cast<LocalFieldCell*>(item);
		if (cell) {
			cell->update();
		}
	}

	if (Keyboard::get(Qt::Key_Shift)) {
		m_scale -= 0.1f;
		m_scale = std::max(m_min_scale, m_scale);
		for (auto view : views()) {
			view->resetTransform();
			view->scale(m_scale, m_scale);
		}
	}
	else {
		m_scale += 0.1f;
		m_scale = std::min(1.0f, m_scale);
		for (auto view : views()) {
			view->resetTransform();
			view->scale(m_scale, m_scale);
		}
	}
}

void load(std::istream& stream) {

}

void save(std::ostream& stream) {

}

//void LocalField::load() {
//	auto filename = getFilename(globalCell());
//	std::ifstream stream{ filename.toStdWString(), std::ios::binary };
//	if (stream.is_open())
//		impl->load(stream);
//}
//
//void LocalField::save() {
//	auto filename = getFilename(globalCell());
//	std::ofstream stream{ filename.toStdWString(), std::ios::binary };
//	if (stream.is_open())
//		impl->save(stream);
//}
//
//LocalField::~LocalField() {
//	//save();
//	impl.reset(nullptr);
//}

float LocalField::cellSize() {
	return 6250;
}

//bool LocalField::hasStoredData(GlobalFieldCell* cell) {
//	auto filename = getFilename(cell);
//	return QFile::exists(filename);
//}
//
//QString LocalField::getFilename(GlobalFieldCell* cell) {
//	auto path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
//	QDir dir{ path };
//	if (!dir.exists("Badziaha"))
//		dir.mkdir("Badziaha");
//	dir.cd("Badziaha");
//	auto filepath = dir.absoluteFilePath("cell_" + QString::number(cell->position.x()) + "_" + QString::number(cell->position.y()) + ".cell");
//	return filepath;
//}

FieldCell* LocalField::cell(int x, int y) {
	return m_cells[x + width()*y].get();
}

FieldCell* LocalField::cell(const QPoint& pos) {
	return cell(pos.x(), pos.y());
}

FieldCell* LocalField::cell(const QPointF& pos) {
	int x = pos.x() / LocalField::cellSize();
	int y = pos.y() / LocalField::cellSize();
	return cell(x, y);
}

void LocalField::keyPressEvent(QKeyEvent *event) {
	//qDebug(__FUNCTION__);
	Keyboard::set(event->key(), true);
	if (event->key() == Qt::Key_I) {
		emit toggleInventory(nullptr);
	}
	event->accept();
}

void LocalField::keyReleaseEvent(QKeyEvent *event) {
	//qDebug(__FUNCTION__);
	Keyboard::set(event->key(), false);
	event->accept();
}

void LocalField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	std::cout << event->scenePos().x() << " " << event->scenePos().y() << std::endl;
	Mouse::set(event->button(), true);
	event->accept();
}

void LocalField::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	//std::cout << event->scenePos().x() / 100.0f << " " << event->scenePos().y() / 100.0f<< std::endl;
	m_last_position = event->scenePos();
	auto player = world()->player();
	if (player) {
		player->setTarget(m_last_position);
	}
	/*if (m_human_unit){
		m_human_unit->setTarget(impl->m_last_position);
	}*/
	updateViews();
}

void LocalField::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	//qDebug(__FUNCTION__);
	Mouse::set(event->button(), false);
	event->accept();
}

float LocalField::cellPhysicalSize() {
	return 256;
}

void LocalField::updateViews() {
	for (auto view : views()) {
		auto player = world()->player();
		if (player) {
			auto pos = player->scenePos();
			//auto v = m_target + (m_last_position - m_target) * 0.5f;
			view->centerOn(pos);
		}
	}
}

//void LocalField::addItemInstance(const QPointF& global_position, ItemPtr item) {
//	auto c = cell(global_position);
//	if (!c) {
//		qDebug() << "Can't find suitable cell in the local field";
//		return;
//	}
//	c->add(global_position, std::move(value));
//	qDebug() << value->name() << "was dropped in the cell" << c->position().x() << c->position().y();
//}
//
//ItemPtr LocalField::removeItemInstance(const Item* value) {
//	for (auto& c : impl->m_cells) {
//		if (c->hasItem(value)) {
//			qDebug() << value->name() << "was taken from the cell" << c->position().x() << c->position().y();
//			return c->remove(value);
//		}
//	}
//	return make_ptr<Item>(nullptr);
//}
//
//bool LocalField::hasItemInstance(const Item* value) const {
//	for (auto& c : impl->m_cells) {
//		if (c->hasItem(value)) {
//			return true;
//		}
//	}
//	return false;
//}
//
//const std::vector<const Item*> LocalField::selectItemInstances(ItemClassType type) const {
//	std::vector<const Item*> result;
//	for (auto& c : impl->m_cells) {
//		for (auto& item : c->items())
//			if (item.item->classType() == type)
//				result.push_back(item.item.get());
//	}
//	return result;
//}
//
//const std::vector<const Item*> LocalField::selectItemInstances(ItemClassType type, QRectF global_rect) const {
//	std::vector<const Item*> result;
//	for (auto& c : impl->m_cells) {
//		for (auto& item : c->items()) {
//			if (global_rect.contains(item.position))
//				result.push_back(item.item.get());
//		}
//	}
//	return result;
//}

void LocalField::addItemInstance(const QPointF& global_position, ItemPtr item) {
	return;
}

ItemPtr LocalField::removeItemInstance(const Item* item) {
	return make_ptr<Item>(nullptr);
}

bool LocalField::hasItemInstance(const Item* item) const {
	return false;
}

const std::vector<const Item*> LocalField::selectItemInstances(ItemClassType type) const {
	return std::vector<const Item*>();
}
const std::vector<const Item*> LocalField::selectItemInstances(ItemClassType type, QRectF rect) const {
	return std::vector<const Item*>();
}

void LocalField::centerOn(const QPointF& target) {
	for (auto v : views()) {
		v->centerOn(target);
	}
}

float LocalField::realWidth() {
	auto cell_size = Options::get<int>(OptionType::CellSize);
	auto local_field_width = Options::get<int>(OptionType::LocalFieldWidth);
	return cell_size * local_field_width;
}

float LocalField::realHeight() {
	auto cell_size = Options::get<int>(OptionType::CellSize);
	auto local_field_height = Options::get<int>(OptionType::LocalFieldHeight);
	return cell_size * local_field_height;
}