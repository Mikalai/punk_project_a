#include <map>
#include <QtGui/qpainter.h>
#include "unit.h"
#include "unit_model.h"

UnitModel::UnitModel(Unit* unit, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_unit{ unit }
{}

QRectF UnitModel::boundingRect() const {
	return QRectF(-15, -25, 150, 125);
}

void UnitModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	painter->setBrush(Qt::BrushStyle::SolidPattern);
	painter->drawRect(-15,-25,30,50);// -10, -10, 20, 20, 5, 5);
	auto pen = painter->pen();
	pen.setWidth(5);
	pen.setColor(QColor{ 255, 0, 0 });
	painter->setPen(pen);
	painter->drawLine(0, 0, 100, 0);
	pen.setColor(QColor{ 0, 255, 0 });
	painter->setPen(pen);
	painter->drawLine(0, 0, 0, 100);
}

