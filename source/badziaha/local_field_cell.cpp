#include <QtCore/qdebug.h>
#include <QtGui/qpainter.h>
#include "items.h"
#include "local_field.h"
#include "resources.h"
#include "global_field.h"
#include "local_field_cell.h"
#include "local_field_item.h"
#include "entity.h"
#include "character.h"
#include "options.h"


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
	for (auto item : childItems()) {
		auto e = qgraphicsitem_cast<Character*>(item);
		if (e) {
			e->update();
		}
	}
}

GlobalFieldCell* LocalFieldCell::globalFieldCell() const {
	return field()->globalCell();
}

float LocalFieldCell::realSize() {
	return Options::get<int>(OptionType::CellSize);
}

void LocalFieldCell::addCharacter(CharacterPtr value) {
	qDebug() << value->name() << "added to local field cell" << pos().x() << pos().y();
	m_characters.push_back(std::move(value));
}

CharacterPtr LocalFieldCell::removeCharacter(Character* value) {
	auto it = std::find_if(m_characters.begin(), m_characters.end(), [value](const CharacterPtr& v) {
		return v.get() == value; });
	if (it == m_characters.end()) {
		qDebug() << value->name() << "not found in the local field cell" << pos().x() << pos().y();
		return make_ptr<Character>(nullptr);
	}
	auto result = std::move(*it);
	m_characters.erase(it);
	return result;
}