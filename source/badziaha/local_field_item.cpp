#include <QtCore/qdebug.h>
#include <QtWidgets/qgraphicsview.h>
#include <QtGui/qpainter.h>
#include "local_field.h"
#include "local_field_cell.h"
#include "global_field_cell.h"
#include "global_field.h"
#include "items.h"
#include "local_field_item.h"

LocalFieldItem::LocalFieldItem(ItemPtr item, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_item{ std::move(item) }
{
	setFlags(QGraphicsItem::GraphicsItemFlag::ItemSendsScenePositionChanges);	
	setToolTip(m_item->ToString());
}

QRectF LocalFieldItem::boundingRect() const {
	return item()->icon().rect();
}

void LocalFieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	auto view = qobject_cast<QGraphicsView*>(widget->parentWidget());
	auto sx = view->transform().m11();
	auto sy = view->transform().m22();
	if (sx != 1) {
		auto brush = painter->brush();
		auto m = QMatrix{};
		m.scale(sx, sy);
		painter->setMatrix(m.inverted(), true);
	}
	painter->drawImage(QPoint{ 0, 0 }, item()->icon());
}

QVariant LocalFieldItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	//qDebug() << __FUNCTION__;

	//auto s = scene();
	auto local_field = qobject_cast<LocalField*>(scene());

	if (change == ItemPositionHasChanged && scene()) {

		//	if we in the current cell do nothing
		QPointF newPos = value.toPointF();
		if (newPos.x() >= 0 && newPos.x() <= LocalFieldCell::realSize()
			&& newPos.y() >= 0 && newPos.y() <= LocalFieldCell::realSize()) {
			//	return nothing. ignored anyway
			return QVariant{};
		}

		//	find world position of the entity
		auto world_to_local_cell = parentItem()->sceneMatrix();
		auto scene_new_pos = newPos * world_to_local_cell;
		//auto scene_new_pos = mapToScene(newPos);

		//	retrieve local field to get global field cell
		if (local_field) {
			//	find transform from world to the global cell (the same a local field)
			auto world_to_local_field = local_field->globalCell()->sceneMatrix().inverted();
			//	get new position in the local field space
			auto pos_in_local_field = scene_new_pos * world_to_local_field;
			//	get new local cell where entity is located
			auto new_cell = local_field->cell(pos_in_local_field);
			//	get new position in the local cell space
			auto new_pos = scene_new_pos * new_cell->sceneMatrix().inverted();
			setParentItem(new_cell);
			setPos(new_pos);
			qDebug() << "LOCAL ITEM CHANGED PARENT" << new_cell->x() << new_cell->y();
		}
	}
	return QGraphicsItem::itemChange(change, value);
}
