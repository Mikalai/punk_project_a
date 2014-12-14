#ifndef _H_FIELD
#define _H_FIELD

#include <QtWidgets/qgraphicsscene.h>
#include <QtWidgets/qgraphicsitem.h>
#include <QtCore/qpoint.h>
#include <QtCore/qdatetime.h>
#include <list>
#include <vector>
#include "time_dependent.h"
#include "item_class_type.h"
#include "fwd_items.h"
#include "fwd_character.h"

struct WeatherStamp;
class Spatial;
class FieldCell;
class World;

#define LOCAL_FIELD_CELL 6250
#define LOCAL_FIELD_SIZE 64

#define GLOBAL_FIELD_CELL_REAL_SIZE (LOCAL_FIELD_CELL * LOCAL_FIELD_SIZE)
#define GLOBAL_FIELD_SIZE 64

#define GLOBAL_FIELD_SIZE 64

class FieldCell : public QGraphicsItem, public TimeDependent {
public:
	FieldCell(QGraphicsItem* parent);
	virtual ~FieldCell() {}
	void addEntity(Spatial* value);
	void removeEntity(Spatial* value);
	std::vector<Spatial*> entities;
};

class Field : public QGraphicsScene {
	Q_OBJECT
public:
	Field(World* world, QObject* parent)
		: QGraphicsScene{ parent }
		, m_world{ world }
	{}

	virtual FieldCell* cell(const QPoint& p) = 0;
	virtual FieldCell* cell(int x, int y) = 0;

	virtual void addCharacterInstance(const QPointF& global_position, CharacterPtr value) = 0;
	virtual void addItemInstance(const QPointF& global_position, ItemPtr item) = 0;
	virtual ItemPtr removeItemInstance(const Item* item) = 0;
	virtual bool hasItemInstance(const Item* item) const = 0;
	virtual const std::vector<const Item*> selectItemInstances(ItemClassType type) const = 0;
	virtual const std::vector<const Item*> selectItemInstances(ItemClassType type, QRectF rect) const = 0;

	WeatherStamp* weather() const;

	World* world() const { return m_world; }
private:
	World* m_world{ nullptr };
};

#endif	//	_H_FIELD