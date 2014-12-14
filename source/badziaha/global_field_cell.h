#ifndef _H_GLOBAL_FIELD_CELL_REAL_SIZE
#define _H_GLOBAL_FIELD_CELL_REAL_SIZE

#include <functional>
#include <QtCore/qpoint.h>
#include <set>
#include <vector>
#include <chrono>
#include "model_type.h"
#include "surface_type.h"
#include "field.h"
#include "time_dependent.h"
#include "fwd_local_field.h"

class Road;
class GlobalField;
class Entity;
class LocalField;

class GlobalFieldCell : public FieldCell {
public:
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

	struct Tls {
		FindPathData path;
	};
	
public:

	enum { Type = QGraphicsItem::UserType + (int)ModelType::GlobalFieldCell };

	int type() const override {
		return Type;
	}

	GlobalFieldCell(GlobalField* field, QGraphicsItem* parent);
	virtual ~GlobalFieldCell();

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

	void update();

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


	//	QGraphicsItem
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	QPoint index() const;

	static int cellSize() { return LOCAL_FIELD_CELL * LOCAL_FIELD_SIZE; }

	const GlobalField* field() const;
	GlobalField* field();

	void setSurface(const SurfaceTypeClass* value) { m_surface = value; }
	const SurfaceTypeClass* surface() const { return m_surface; }

	LocalField* localField();

	void addCharacterInstance(const QPointF& global_position, CharacterPtr value);
	void addItemInstance(const QPointF& global_position, ItemPtr item);

private:
	LocalFieldPtr m_local_field{ make_ptr<LocalField>(nullptr) };
	std::vector<Tls> tls;
	std::set<Road*> m_roads;
	GlobalField* m_field{ nullptr };
	const SurfaceTypeClass* m_surface{ nullptr };

	std::vector < std::function<void(LocalField*)>> on_post_create;
};

#endif	//	_H_GLOBAL_FIELD_CELL_REAL_SIZE