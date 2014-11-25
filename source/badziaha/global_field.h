#ifndef _H_GLOBAL_FIELD
#define _H_GLOBAL_FIELD

#include <set>
#include <deque>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <QtCore/qobject.h>
#include <QtCore/qdatetime.h>
#include <QtWidgets/qgraphicsscene.h>
#include "time_dependent.h"
#include "weather.h"
#include "field.h"
#include "global_field_cell.h"
#include "fwd_global_field.h"

class World;
class GlobalFieldCell;
class Squad;
class City;
class Road;
class Entity; 
class Construction;
class Building;
struct WeatherStamp;

struct FindPathResult {
	std::list<GlobalFieldCell*> path;
	QPoint start;
	QPoint end;
	bool has_result{ false };
	bool has_path{ false };
	bool is_used{ false };
	bool is_canceled{ false };
};

class GlobalField : public Field, public TimeDependent {
	Q_OBJECT;
public:

	struct Tls {
		int find_path_magic{ 0 };
	};

	enum class InteractionMode {
		Select,
		ControlSquad,
		BuildRoad,
		Building
	};

public:
	GlobalField(World* world, QObject* parent = nullptr);
	virtual ~GlobalField();
	void Create();

	void neighbourCells(GlobalFieldCell* cell, std::vector<GlobalFieldCell*>& cells);

	int width() const {
		return m_width;
	}

	int height() const {
		return m_height;
	}

	bool getPath(const QPoint& start, const QPoint& end, std::list<GlobalFieldCell*>& path);
	FindPathResult* beginGetPath(const QPoint& start, const QPoint& end);
	void endGetPath(FindPathResult* result);
	void cancelGetPath(FindPathResult* result);

	static int cellSize();
	static float timeStep();

	Tls* getTls(int index) {
		return &m_tls.at(index);
	}

	int getTlsIndex() {
		return m_tls_index.at(std::this_thread::get_id());
	}

	void allocateTls(std::thread::id id) {
		auto size = m_tls_index.size();
		m_tls_index[id] = (int)size;
		m_tls.resize(m_tls_index.size());
	}

	//	roads
	std::set<Road*>& roads() {
		return m_roads;
	}

	//	buildings
	std::vector<Construction*> buildings() {
		return m_building;
	}

	// delayed destroying
	void moveToTrash(Entity* value) {
		m_entities_to_delete.push_back(value);
	}

	Entity* player();

	void update() override;

	//	Field impl
	void addItemInstance(const QPointF& global_position, ItemPtr item) override;
	ItemPtr removeItemInstance(const Item* item) override;
	bool hasItemInstance(const Item* item) const override;
	const std::vector<const Item*> selectItemInstances(ItemClassType type) const override;
	const std::vector<const Item*> selectItemInstances(ItemClassType type, QRectF rect) const override;
	GlobalFieldCell* cell(const QPoint& p) override;

	GlobalFieldCell* cell(int x, int y) override {
		return cell(QPoint{ x, y });
	}

	GlobalFieldCell* cell(const QPointF& p) {
		return cell(index(p));
	}
	 
	const QPoint index(const QPointF& p) {
		int x = (int)p.x() / cellSize();
		int y = (int)p.y() / cellSize();
		return QPoint{ x, y };
	}

	const SurfaceTypeClass* surface(const QPointF& position);

public slots:
	void onSelectionChanged();
	void terminate();
	void setInteractionMode(InteractionMode value);

signals:
	void citySelected(City* city);
	void selectionDropped();
	void fieldCellPressed(QGraphicsSceneMouseEvent* event, GlobalFieldCell* cell);
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
private:
	
	void addBuilding(Construction* value);
	void removeBuilding(Construction* value);
	void addRoad(Road* value);
	void removeRoad(Road* value);
	void addSquad(Squad* value);
	void removeSquad(Squad* value);
	void addCity(City* value);
	void removeCity(City* value);

	//	path finding data
	static void pathFinderFunc(GlobalField* field);
	bool findPath(const QPoint& start, const QPoint& end, std::list<GlobalFieldCell*>& cells);
	bool findPathA(GlobalFieldCell* start, GlobalFieldCell* end, std::list<GlobalFieldCell*>& cells);
	float heuristicCost(GlobalFieldCell* cell, GlobalFieldCell* end);
	float distanceCost(GlobalFieldCell* start, GlobalFieldCell* end);
	GlobalFieldCell* minimalFullCost(std::vector<GlobalFieldCell*>& cells, int tls_index);	
	bool reconstructPath(GlobalFieldCell* start, GlobalFieldCell* end, std::list<GlobalFieldCell*>& cells, int tls_index);

	//	initialization stuff
	void Create(float grass, float water, float sand, float dirt, float forest, float rocks, bool island, int sea_width);

private:

	//	field description
	int m_width{ 64};
	int m_height{ 64};
	std::vector<GlobalFieldCellPtr> m_cells;

	//	squads data
	std::vector<Squad*> m_squads;
	std::set<Squad*> m_selected_squads;
	int m_max_squad_count{ 5 };

	// cities data
	std::vector<City*> m_cities;
	int m_max_city_count{ 10 };

	//	path finding 
	bool m_terminate{ false };
	std::thread m_path_finder_thread;
	std::list<FindPathResult> m_path_find_result;
	std::list<FindPathResult*> m_path_find_tasks;
	std::condition_variable m_path_find_cond;
	std::mutex m_path_find_mutex;

	//	thread local data
	std::vector<Tls> m_tls;
	std::map<std::thread::id, int> m_tls_index;

	//	field update data
	int m_last_row_update{ 0 };

	//	all the roads 
	std::set<Road*> m_roads;

	//	current interaction mode
	InteractionMode m_mode{ InteractionMode::Select };

	//	entities: Buildings
	std::vector<Construction*> m_building;

	//	pending removing
	std::vector<Entity*> m_entities_to_delete;

private:
	friend void addSquad(GlobalField* field, Squad* squad);
	friend void removeSquad(GlobalField* field, Squad* squad);
	friend void addCity(GlobalField* field, City* city);
	friend void removeCity(GlobalField* field, City* city);
	friend void addBuilding(GlobalField* field, Construction* city);
	friend void removeBuilding(GlobalField* field, Construction* city);
	friend void addRoad(GlobalField* field, Road* road);
	friend void removeRoad(GlobalField* field, Road* road);
};

void addSquad(GlobalField* field, Squad* squad);
void removeSquad(GlobalField* field, Squad* squad);
void addCity(GlobalField* field, City* city);
void removeCity(GlobalField* field, City* city);
void addBuilding(GlobalField* field, Construction* construction);
void removeBuilding(GlobalField* field, Construction* construction);
void addRoad(GlobalField* field, Road* road);
void removeRoad(GlobalField* field, Road* road);

#endif	//	_H_GLOBAL_FIELD