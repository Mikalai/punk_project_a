#include <QtGui/qpainter.h>
#include <algorithm>
#include <math.h>
#include "global_field_cell.h"
#include "global_field.h"
#include "road_graphics_item.h"
#include "road.h"

RoadGraphicsItem::RoadGraphicsItem(Road* value, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_road{ value }
{
	QPolygonF p;
	for (auto& cell : m_road->getPath()) {
		p.append(cell->position * GlobalField::cellSize());
	}
	m_bbox = p.boundingRect();
}

QRectF RoadGraphicsItem::boundingRect() const {
	return m_bbox;
}

void RoadGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	auto brush = painter->brush();
	brush.setTextureImage(QImage{ ":/images/road.png" });
	brush.setStyle(Qt::BrushStyle::TexturePattern);
	auto& path = m_road->getPath();
	auto cur = path.begin();
	auto next = cur;
	std::advance(next, 1);
	for (; next != path.end(); ++cur, ++next) {
		auto& cur_cell = *cur;
		auto& next_cell = *next;
		auto delta = next_cell->position - cur_cell->position;
		delta = delta / delta.manhattanLength();
		auto angle = atan2(delta.x(), delta.y()) * 45 / atan(1);
		QMatrix m;
		m.rotate(angle);
		brush.setMatrix(m);
		//painter->setBrush(brush);

		auto pen = painter->pen();
		pen.setWidth(10);
		pen.setStyle(Qt::PenStyle::SolidLine);
		pen.setBrush(brush);
		pen.setCosmetic(false);
		painter->setPen(pen);

		painter->drawLine(cur_cell->position.x() * GlobalField::cellSize(), 
			cur_cell->position.y()*GlobalField::cellSize(),
			next_cell->position.x() * GlobalField::cellSize(),
			next_cell->position.y() * GlobalField::cellSize());
	}
}
