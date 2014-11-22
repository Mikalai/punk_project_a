#ifndef _H_WORLD
#define _H_WORLD

#include <memory>
#include <QtCore/qobject.h>
#include <QtCore/qdatetime.h>
#include "time_dependent.h"
#include "weather.h"

struct WeatherStamp;
class GlobalField;
class LocalField;

class World : public QObject, public TimeDependent {
	Q_OBJECT
public:

	virtual ~World();

	void create();
	void destroy();

	GlobalField* globalField() {
		return m_global_field;
	}

	LocalField* localField() {
		return m_local_field;
	}

	void setLocalField(LocalField* value);

	WeatherStamp* weather() {
		return &m_current_weather;
	}

public slots:
	void updateByTimer();

signals:
	void timeChanged(const QDateTime& dt);
	void weatherChanged(const WeatherStamp&);

private:
	//	time managment
	QDateTime m_current_time;

	GlobalField* m_global_field{ nullptr };
	LocalField* m_local_field{ nullptr };
	WeatherStamp m_current_weather;
};

#endif	//	_H_WORLD