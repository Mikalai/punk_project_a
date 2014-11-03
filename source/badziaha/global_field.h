#ifndef _H_GLOBAL_FIELD
#define _H_GLOBAL_FIELD

#include <set>
#include <deque>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <QtCore/qobject.h>
#include <QtWidgets/qgraphicsscene.h>

struct GlobalFieldCell;
class Squad;
class City;
class Road;
class Entity; 

struct FindPathResult {
	std::list<GlobalFieldCell*> path;
	QPoint start;
	QPoint end;
	bool has_result{ false };
	bool has_path{ false };
	bool is_used{ false };
	bool is_canceled{ false };
};


class GlobalField : public QGraphicsScene {
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
	GlobalField(QObject* parent = nullptr);
	virtual ~GlobalField();
	void Create();
	void addSquad(Squad* value);
	void removeSquad(Squad* value);
	void addCity(City* value);

	GlobalFieldCell* getCell(const QPoint& p);
	GlobalFieldCell* getCell(int x, int y) {
		return getCell(QPoint{ x, y });
	}

	int getWidth() const {
		return m_width;
	}

	int getHeight() const {
		return m_height;
	}

	bool getPath(const QPoint& start, const QPoint& end, std::list<GlobalFieldCell*>& path);
	FindPathResult* beginGetPath(const QPoint& start, const QPoint& end);
	void endGetPath(FindPathResult* result);
	void cancelGetPath(FindPathResult* result);

	static float cellSize();
	static float timeStep();

	Tls* getTls(int index) {
		return &m_tls.at(index);
	}

	int getTlsIndex() {
		return m_tls_index.at(std::this_thread::get_id());
	}

	void allocateTls(std::thread::id id) {
		auto size = m_tls_index.size();
		m_tls_index[id] = size;
		m_tls.resize(m_tls_index.size());
	}

	//	roads
	void addRoad(Road* value);

	void removeRoad(Road* value);

	std::set<Road*>& getRoads() {
		return m_roads;
	}

	//	buildings
	void addBuilding(Entity* value);
	void removeBuilding(Entity* value);

	std::vector<Entity*> getBuilding() {
		return m_building;
	}

public slots:
	void update();
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
	
	//	path finding data
	static void pathFinderFunc(GlobalField* field);
	bool findPath(const QPoint& start, const QPoint& end, std::list<GlobalFieldCell*>& cells);
	bool findPathA(GlobalFieldCell* start, GlobalFieldCell* end, std::list<GlobalFieldCell*>& cells);
	float heuristicCost(GlobalFieldCell* cell, GlobalFieldCell* end);
	float distanceCost(GlobalFieldCell* start, GlobalFieldCell* end);
	GlobalFieldCell* minimalFullCost(std::vector<GlobalFieldCell*>& cells, int tls_index);	
	bool reconstructPath(GlobalFieldCell* start, GlobalFieldCell* end, std::list<GlobalFieldCell*>& cells, int tls_index);
	void neighbourCells(GlobalFieldCell* cell, std::vector<GlobalFieldCell*>& cells);

	//	initialization stuff
	void Create(float grass, float water, float sand, float dirt, float forest, float rocks, bool island, int sea_width);

private:

	//	field description
	int m_width{ 64};
	int m_height{ 64};
	std::vector<GlobalFieldCell> m_cells;

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
	std::vector<Entity*> m_building;
};

#endif	//	_H_GLOBAL_FIELD