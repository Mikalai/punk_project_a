#include <QtGui/qpixmap.h>
#include <QtWidgets/qgraphicssceneevent.h>
#include <QtGui/qpainter.h>
#include "global_field.h"
#include "squad.h"
#include "squad_graphics_item.h"
#include "resources.h"

SquadGraphicsItem::SquadGraphicsItem(Squad* squad, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_squad{ squad }
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF SquadGraphicsItem::boundingRect() const {
	auto image = Resources::instance()->getSquadImage();
	float w = image->width();
	float h = image->height();
	return QRectF{ -w / 2.0, -h / 2.0, w, h };
}

void SquadGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	auto image = Resources::instance()->getSquadImage();
	float w = image->width();
	float h = image->height();
	painter->drawImage(QPointF{ -w / 2, -h / 2 }, *image);
}

//void SquadGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent * event) override {
//	event->accept();
//}

//void SquadGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
//	event->accept();
//	m_squad->select();
//}
