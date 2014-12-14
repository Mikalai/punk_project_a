#include <QtCore/qdebug.h>
#include <QtWidgets/qgraphicsitem.h>
#include <QtGui/qpainter.h>
#include "entity.h"
#include "global_field_cell.h"
#include "global_field.h"
#include "local_field.h"
#include "constants.h"
#include "keys.h"
#include "local_field_cell.h"
#include "local_field_item.h"
#include "options.h"

Entity::Entity(GlobalField* field, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
	, m_field{ field }
{
	setFlags(QGraphicsItem::GraphicsItemFlag::ItemSendsScenePositionChanges);
	//m_last_update = std::chrono::high_resolution_clock::now();
}

Entity::~Entity() {
	qDebug() << "Entity destroyed";
}

//void Entity::setModel(QGraphicsItem* item) {
//	QGraphicsScene* scene = nullptr;
//	if (m_model) {
//		scene = m_model->scene();
//		delete m_model;
//	}
//	m_model = item;
//	if (scene && m_model ) {
//		scene->addItem(m_model);
//	}
//	updateModelTransform();
//}


//void Entity::updateModelTransform() {
//
//	if (!m_model)
//		return;
//
//	float size = GlobalField::cellSize();
//	QMatrix m;
//	m.translate(fullPosition().x() * size, fullPosition().y() * size);
//	m_model->setTransform(QTransform{ m });
//	m_model->update();
//}
//
//void Entity::OnPositionChanged() {
//	updateModelTransform();
//}

QRectF Entity::boundingRect() const {
	return QRectF{ -15, -30, 30, 60 };
}

void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	auto brush = painter->brush();
	brush.setStyle(Qt::BrushStyle::SolidPattern);
	painter->setBrush(brush);
	painter->drawRect(boundingRect());
}

const Field* Entity::field() const { 
	return m_field; 
}

Field* Entity::field() { 
	return m_field; 
}

QVariant Entity::itemChange(GraphicsItemChange change, const QVariant &value)
{
	//qDebug() << __FUNCTION__;

	//auto s = scene();
	auto local_field = qobject_cast<LocalField*>(scene());
	if (local_field)
		local_field->centerOn(this->scenePos());

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
			qDebug() << "Parent cell has been changed to" << new_cell->x() << new_cell->y();
			qDebug() << "Entity scene pos" << scene_new_pos.x() << scene_new_pos.y();
			qDebug() << "Entity local_pos" << new_pos.x() << new_pos.y();
			qDebug() << "Entity old_pos" << newPos.x() << newPos.y();
			qDebug() << "Entity pos in local field" << pos_in_local_field.x() << pos_in_local_field.y();
		}
	}
	return QGraphicsItem::itemChange(change, value);
}

void Entity::setTarget(const QPointF& value) {
	m_target = value;
	auto dir = m_target - scenePos();
	dir = dir / dir.manhattanLength();
	auto angle = atan2f(dir.y(), dir.x()) * Const::RadToDeg;
	setRotation(angle);
}

void Entity::update() {
	TimeDependent::update();
	auto dt = getTimeStep();

	if (isHumanControl()) {

		QPointF dir{ 0, 0 };
		if (Keyboard::get(Qt::Key_W))
			dir.setX(dir.x() + 1);
		if (Keyboard::get(Qt::Key_S))
			dir.setX(dir.x() - 1);
		if (Keyboard::get(Qt::Key_D))
			dir.setY(dir.y() + 1);
		if (Keyboard::get(Qt::Key_A))
			dir.setY(dir.y() - 1);

		auto l = dir.manhattanLength();
		if (l > 1e-3f) {
			dir = dir / dir.manhattanLength();

			QMatrix rm;
			rm.rotate(rotation());
			dir = dir * rm;

			auto p = pos();
			auto new_pos = p + dir * dt * 140;
			setPos(new_pos);

			auto bbox = sceneBoundingRect();
			auto dst = sqrtf(bbox.width()*bbox.width() + bbox.height() *bbox.height()) * 1.01;
			for (auto child : parentItem()->childItems()) {
				if (child == this)
					continue;				
				if (child->type() == LocalFieldItem::Type)
					continue;
				if (child->sceneBoundingRect().intersects(bbox)) {
					auto norm = (pos() - child->pos()).manhattanLength();
					auto dir = (child->pos()- pos()) / norm;
					child->setPos(pos() + dir * dst);
					//setPos(p);
					break;
				}
			}
		}
	}
}