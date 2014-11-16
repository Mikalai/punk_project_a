#ifndef _H_ENTITY
#define _H_ENTITY

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include <chrono>
#include "time_dependent.h"
#include "spatial.h"

class QGraphicsItem;
class GlobalField;
class Building;

class Entity : public QObject, public TimeDependent, public Spatial {
public:

	Entity(GlobalField* field, QObject* parent = nullptr);

	virtual ~Entity();

	QGraphicsItem* model() {
		return m_model;
	}

	void setModel(QGraphicsItem* item);

	void setHumanControl(bool value) {
		m_human_control = value;
	}

	bool isHumanControl() const {
		return m_human_control;
	}


protected:
	void OnPositionChanged() override;
private:
	void updateModelTransform();

private:
	

	/*std::chrono::high_resolution_clock::time_point m_last_update;
	float m_dt{ 0 };*/
	bool m_human_control{ false };
	QGraphicsItem* m_model{ nullptr };
	Building* m_building{ nullptr };
};

#endif	//	_H_BUILDING