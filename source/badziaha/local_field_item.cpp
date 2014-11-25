#include <QtGui/qpainter.h>
#include "local_field_item.h"

LocalFieldItem::LocalFieldItem(ItemPtr item, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_item{ std::move(item) }
{}

QRectF LocalFieldItem::boundingRect() const {
	return QRectF{ 0, 0, 50, 50 };
}

void LocalFieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->drawRect(boundingRect());
}