#include <QtGui/qpainter.h>
#include <QtWidgets/qgraphicssceneevent.h>
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
//	setFlag(QGraphicsItem::ItemIsSelectable);
	updateBoundingBox();
	setZValue(0.05f);
}

QRectF RoadGraphicsItem::boundingRect() const {
	return m_bbox;
}

void RoadGraphicsItem::updateBoundingBox() {
	QPolygonF p;
	for (auto& cell : m_road->getPath()) {
		p.append(cell->position * GlobalField::cellSize());
	}
	prepareGeometryChange();
	m_bbox = p.boundingRect();
	//update(m_bbox);	
	////auto s = scene();
	////if (s) {
	////	s->update();
	////}
}

void RoadGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	auto brush = painter->brush();
	brush.setTextureImage(QImage{ ":/images/road.png" });
	brush.setStyle(Qt::BrushStyle::TexturePattern);
	auto& path = m_road->getPath();
	if (path.empty())
		return;

	auto cur = path.begin();
	auto next = cur;
	std::advance(next, 1);
	for (; next != path.end(); ++cur, ++next) {
		auto& cur_cell = *cur;
		auto& next_cell = *next;
		auto delta = next_cell->position - cur_cell->position;
		delta = delta / delta.manhattanLength();
		auto angle = atan2(delta.y(), delta.x()) * 45 / atan(1);
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

void RoadGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	qDebug(__FUNCTION__);
	QGraphicsItem::mousePressEvent(event);
	event->ignore();
}