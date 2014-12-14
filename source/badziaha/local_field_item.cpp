#include <QtGui/qpainter.h>
#include "items.h"
#include "local_field_item.h"

LocalFieldItem::LocalFieldItem(ItemPtr item, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_item{ std::move(item) }
{}

QRectF LocalFieldItem::boundingRect() const {
	return item()->icon().rect();
}

void LocalFieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->drawImage(QPoint{ 0, 0 }, item()->icon());
}