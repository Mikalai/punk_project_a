#include <QtCore/qpoint.h>
#include <set>
#include <vector>
#include <chrono>
#include "surface_type.h"

class Road;
struct GlobalFieldCell;
class Entity;

struct FindPathData {
	int find_path_magic{ 0 };
	int find_path_number{ 0 };
	bool find_path_scanned{ false };
	float find_path_cost{ 0 };
	float find_path_heuristic_const{ 0 };
	float full_path_cost{ 0 };
	bool closed{ false };
	int opened{ -1 };
	GlobalFieldCell* source{ nullptr };
};

struct GlobalFieldCell {

	struct Tls {
		FindPathData path;
	};

	SurfaceType ground{ SurfaceType::Grass };
	QPoint position{ 0, 0 };
	std::vector<Entity*> entities;

public:

	FindPathData* findPath(int index) {
		return &getTls(index)->path;
	}

	Tls* getTls(int index) {
		return &tls.at(index);
	}

	void setTlsCount(int count) {
		tls.resize(count);
	}

	float getBaseMoveDifficulty() const;

	GlobalFieldCell();

	void update();

	void addEntity(Entity* value);
	void removeEntity(Entity* value);

	void addRoad(Road* value) {
		m_roads.insert(value);
	}

	void removeRoad(Road* value) {
		m_roads.erase(value);
	}

	std::set<Road*>& getRoads() {
		return m_roads;
	}

	bool isNeighbour(GlobalFieldCell* cell) const;

	//	Next is a set of function to generate different entities in the cell.
	//	Constructions, resources, items. Generation is used to reduce memory consumptions

	//	returns random generator seed
	int magic() const;

private:
	std::chrono::high_resolution_clock::time_point last_update;
	std::vector<Tls> tls;
	std::set<Road*> m_roads;
};