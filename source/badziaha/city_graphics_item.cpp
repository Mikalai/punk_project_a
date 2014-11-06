#include <QtGui/qpainter.h>
#include "city_graphics_item.h"
#include "city.h"
#include "city_task.h"
#include "resources.h"

CityGraphicsItem::CityGraphicsItem(City* city, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_city{ city }
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setZValue(0.1f);
}

QRectF CityGraphicsItem::boundingRect() const {
	auto image = Resources::instance()->getCityImage();
	float w = image->width();
	float h = image->height();
	return QRectF{ -w / 2.0, -h / 2.0, w, h };
}

void CityGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	auto image = Resources::instance()->getCityImage();
	float w = image->width();
	float h = image->height();
	painter->drawImage(QPointF{ -w / 2, -h / 2 }, *image);
}