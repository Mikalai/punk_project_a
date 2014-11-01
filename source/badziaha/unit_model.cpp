#include <map>
#include <QtGui/qpainter.h>
#include "unit_model.h"

UnitModel::UnitModel(QGraphicsItem* parent)
	: QGraphicsItem{ parent }
{}

QRectF UnitModel::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
		20 + penWidth, 20 + penWidth);
}

void UnitModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	//painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
}

