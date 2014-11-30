#include <QtCore/qdebug.h>
#include <QtWidgets/qgraphicsitem.h>
#include <QtGui/qpainter.h>
#include "entity.h"
#include "global_field_cell.h"
#include "global_field.h"
#include "local_field.h"

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
	qDebug() << __FUNCTION__;

	auto s = scene();

	LocalField* local_field = qobject_cast<LocalField*>(scene());
	GlobalField* global_field = qobject_cast<GlobalField*>(scene());

	if (change == ItemPositionChange && scene()) {
		// value is the new position.
		QPointF newPos = value.toPointF();
		if (global_field) {
			GlobalFieldCell* cur = qgraphicsitem_cast<GlobalFieldCell*>(global_field->cell(newPos));
			GlobalFieldCell* old = qgraphicsitem_cast<GlobalFieldCell*>(parentItem());
			if (cur != old) {
				setParentItem(cur);
			}
		}
	}
	return QGraphicsItem::itemChange(change, value);
}