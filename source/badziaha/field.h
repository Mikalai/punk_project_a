#ifndef _H_FIELD
#define _H_FIELD

#include <QtWidgets/qgraphicsscene.h>
#include <QtCore/qpoint.h>
#include <QtCore/qdatetime.h>
#include <list>
#include <vector>

struct WeatherStamp;
class Spatial;
class FieldCell;
class World;

class FieldCell {
public:
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

	WeatherStamp* weather() const;

private:
	World* m_world{ nullptr };
};

#endif	//	_H_FIELD