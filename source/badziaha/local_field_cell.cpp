#include <QtGui/qpainter.h>
#include "items.h"
#include "local_field.h"
#include "resources.h"
#include "global_field.h"
#include "local_field_cell.h"
#include "local_field_item.h"


LocalFieldCell::LocalFieldCell(const QPointF& global_position, QGraphicsItem* parent)
	: FieldCell{ parent }
{
	QMatrix m;
	m.translate(global_position.x(), global_position.y());
	setTransform(QTransform{ m });
	setZValue(0.0f);
}

QBrush LocalFieldCell::getGroundBrush() const {
	return QBrush{ "red" };// field()->cell(scenePos()) { *Resources::instance()->getImage(m_cell->globalCell()->ground) };
}

LocalField* LocalFieldCell::field() const {
	return qobject_cast<LocalField*>(scene());
}

QRectF LocalFieldCell::boundingRect() const {
	auto size = LocalField::cellSize();
	return QRectF{ 0, 0, size, size };
}

void LocalFieldCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	auto size = LocalField::cellSize();
	auto brush = painter->brush();// getGroundBrush();
	brush.setTextureImage(globalFieldCell()->surface()->icon());
	auto pen = painter->pen();
	pen.setStyle(Qt::PenStyle::NoPen);
	painter->setPen(pen);
	painter->setBrush(brush);
	painter->drawRect(0, 0, size, size);

	/*for (auto& child : childItems()) {
		auto item = qgraphicsitem_cast<
		painter->drawImage(item.position, item.item->icon());
	}*/
}

void LocalFieldCell::add(QPointF local_position, ItemPtr value) {
	LocalFieldItem* item = new LocalFieldItem{ std::move(value), this };
	item->setPos(local_position);
}

bool LocalFieldCell::hasItem(const Item* value) {
	auto children = childItems();
	auto it = std::find_if(children.begin(), children.end(), [value](const QGraphicsItem* item) {
		if (item->type() != LocalFieldItem::Type)
			return false;
		const LocalFieldItem* field_item = static_cast<const LocalFieldItem*>(item);
		return field_item->item() == value;
	});
	return it != children.end();
}

ItemPtr LocalFieldCell::remove(const Item* value) {
	auto children = childItems();
	auto it = std::find_if(children.begin(), children.end(), [value](const QGraphicsItem* item) {
		const LocalFieldItem* field_item = qgraphicsitem_cast<const LocalFieldItem*>(item);
		if (!field_item)
			return false;
		return field_item->item() == value;
	});
	if (it == children.end())
		return make_ptr<Item>(nullptr);
	LocalFieldItem* field_item = static_cast<LocalFieldItem*>(*it);
	auto result = field_item->removeItem();
	delete field_item;
	return result;
}

const std::vector<const Item*> LocalFieldCell::items() const {
	std::vector<const Item*> result;
	auto children = childItems();
	for (auto& child : children) {
		LocalFieldItem* item = qgraphicsitem_cast<LocalFieldItem*>(child);
		if (!item)
			continue;
		result.push_back(item->item());
	}
	return result;
}

void LocalFieldCell::update() {
	TimeDependent::update();
	auto dt = getTimeStep();
}

GlobalFieldCell* LocalFieldCell::globalFieldCell() const {
	return field()->globalCell();
}