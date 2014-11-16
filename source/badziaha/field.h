#ifndef _H_FIELD
#define _H_FIELD

#include <QtWidgets/qgraphicsscene.h>
#include <QtCore/qpoint.h>
#include <QtCore/qdatetime.h>
#include <list>
#include <vector>
#include "weather.h"

class Spatial;
class FieldCell;

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
	Field(QObject* parent)
		: QGraphicsScene{ parent }
	{}

	virtual FieldCell* cell(const QPoint& p) = 0;
	virtual FieldCell* cell(int x, int y) = 0;

	WeatherStamp* weather() {
		return &m_weather;
	}

signals:
	void weatherChanged(const WeatherStamp& value);
	void timeChanged(const QDateTime& dt);

private:
	// current weather state
	WeatherStamp m_weather;
	//	time managment
	QDateTime m_current_time;
};

#endif	//	_H_FIELD