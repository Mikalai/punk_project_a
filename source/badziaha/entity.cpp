#include <QtWidgets/qgraphicsitem.h>
#include "entity.h"
#include "global_field_cell.h"
#include "global_field.h"

Entity::Entity(GlobalField* field, QObject* parent)
	: QObject{ parent }
	, Spatial{ field }
{
	//m_last_update = std::chrono::high_resolution_clock::now();
}

Entity::~Entity() {
	delete m_model;
	m_model = nullptr;
}

void Entity::setModel(QGraphicsItem* item) {
	QGraphicsScene* scene = nullptr;
	if (m_model) {
		scene = m_model->scene();
		delete m_model;
	}
	m_model = item;
	if (scene && m_model ) {
		scene->addItem(m_model);
	}
	updateModelTransform();
}


void Entity::updateModelTransform() {

	if (!m_model)
		return;

	float size = GlobalField::cellSize();
	QMatrix m;
	m.translate(fullPosition().x() * size, fullPosition().y() * size);
	m_model->setTransform(QTransform{ m });
	m_model->update();
}

void Entity::OnPositionChanged() {
	updateModelTransform();
}