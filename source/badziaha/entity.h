#ifndef _H_ENTITY
#define _H_ENTITY

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include <chrono>
#include "time_dependent.h"

class QGraphicsItem;
class GlobalField;

class Entity : public QObject, public TimeDependent {
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

	void setPosition(QPointF value);
	void setPosition(int x, int y);
	void setPosition(int x, int y, float dx, float dy);

	const QPoint& position() const {
		return m_position;
	}

	const QPoint& prevPosition() const {
		return m_prev_position;
	}

	const QPointF fullPosition() const {
		return QPointF{ m_position.x() + m_offset.x(), m_position.y() + m_offset.y() };
	}

	void move(float dx, float dy);

	GlobalField* field() {
		return m_field;
	}

	const GlobalField* field() const {
		return m_field;
	}

private:
	void updateModelTransform();

private:
	QPoint m_prev_position{ 0, 0 };
	QPoint m_position{ 0, 0 };
	QPointF m_offset{ 0, 0 };

	/*std::chrono::high_resolution_clock::time_point m_last_update;
	float m_dt{ 0 };*/
	bool m_human_control{ false };
	QGraphicsItem* m_model{ nullptr };
	GlobalField* m_field{ nullptr };
};

#endif	//	_H_BUILDING