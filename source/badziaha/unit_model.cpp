#include <map>
#include <QtGui/qpainter.h>
#include "unit.h"
#include "unit_model.h"

UnitModel::UnitModel(Unit* unit, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_unit{ unit }
{}

QRectF UnitModel::boundingRect() const {
	return QRectF(-0.5, -0.5, 1, 1);
}

void UnitModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	painter->setBrush(Qt::BrushStyle::SolidPattern);
	painter->drawRect(boundingRect());// -10, -10, 20, 20, 5, 5);
}

