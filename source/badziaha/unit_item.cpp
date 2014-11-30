#include <QtGui/qpainter.h>
#include "unit.h"
#include "unit_item.h"

UnitItem::UnitItem(Unit* unit, QGraphicsItem* item)
	: QGraphicsItem{ item }
	, m_unit{ unit } {
}

QRectF UnitItem::boundingRect() const {
	return QRectF{ -40, -20, 80, 40 };
}

void UnitItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	//setTransform(QTransform{ m_unit->getTransform() });
	painter->drawRect(boundingRect());
	painter->drawLine(0, 0, 50, 0);
}
