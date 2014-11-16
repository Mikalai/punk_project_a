#ifndef _H_UNIT
#define _H_UNIT

#include <QtCore/qobject.h>
#include <QtGui/qtransform.h>
#include <QtCore/qpoint.h>
#include "time_dependent.h"

class QGraphicsItem;
class Character;
class LocalField;

class Unit : public QObject, public TimeDependent {
	Q_OBJECT;

public:
	Unit(LocalField* field, Character* character, int squad_id, QObject* parent = nullptr);

	Character* character() { return m_character; }

	QGraphicsItem* model() { return m_model; }
	float rotation() const { return m_rotation; }
	QPointF position() const { return m_position; }
	void setPosition(QPointF value);
	LocalField* field() { return m_field; }

	QMatrix getTransform() const;

	bool isHumanControl() const;

	void update() override;

	QPointF direction() const;

	int squadId() const {
		return m_squad_id;
	}

	void setTarget(const QPointF& value);
	const QPointF& target() const { return m_target; }

private:
	void updateTransform();

private:
	LocalField* m_field{ nullptr };
	QPointF m_position{ 0, 0 };
	float m_rotation{ 0 };
	Character* m_character{ nullptr };
	int m_squad_id{ -1 };
	QGraphicsItem* m_model{ nullptr };
	//	target in scene coordinates
	QPointF m_target;
};
#endif	//	_H_UNIT