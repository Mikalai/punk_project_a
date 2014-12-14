#ifndef _H_ENTITY
#define _H_ENTITY

#include <QtWidgets/qgraphicsitem.h>
#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include <chrono>
#include "time_dependent.h"
#include "spatial.h"
#include "model_type.h"

class QPainter;
class QWidget;
class QGraphicsItem;
class GlobalField;
class Building;

class Entity : public QObject, public QGraphicsItem, public TimeDependent {
public:

	Entity(GlobalField* field, QGraphicsItem* parent);

	virtual ~Entity();

	void setHumanControl(bool value) {
		m_human_control = value;
	}

	bool isHumanControl() const {
		return m_human_control;
	}

	void move(float dx, float dy);

	void update();

	//	QGraphicsItem
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
	QRectF boundingRect() const override;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	
	enum { Type = QGraphicsItem::UserType + (int)ModelType::Entity };

	int type() const override {
		return Type;
	}

	const Field* field() const;
	Field* field();

	void setTarget(const QPointF& target);
	const QPointF& target() { return m_target; }
private:


private:
	QPointF m_target;
	bool m_human_control{ false };
	GlobalField* m_field{ nullptr };
};

#endif	//	_H_BUILDING