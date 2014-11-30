#ifndef _H_UNIT
#define _H_UNIT

#include <QtCore/qobject.h>
#include <QtGui/qtransform.h>
#include <QtWidgets/qgraphicsitem.h>
#include <QtCore/qpoint.h>
#include "time_dependent.h"

class QGraphicsItem;
class Character;
class LocalField;

class Unit : public QObject, public QGraphicsItem, public TimeDependent {
	Q_OBJECT;

public:
	Unit(LocalField* field, Character* character, int squad_id, QGraphicsItem* parent = nullptr);

	Character* character() { return m_character; }

	LocalField* field() { return m_field; }

	bool isHumanControl() const;

	void update() override;

	QPointF direction() const;

	int squadId() const {
		return m_squad_id;
	}

	void setTarget(const QPointF& value);
	const QPointF& target() const { return m_target; }

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	void updateTransform();

private:
	LocalField* m_field{ nullptr };
	Character* m_character{ nullptr };
	int m_squad_id{ -1 };
	//	target in scene coordinates
	QPointF m_target;
};
#endif	//	_H_UNIT