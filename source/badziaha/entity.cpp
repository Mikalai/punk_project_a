#include <QtWidgets/qgraphicsitem.h>
#include "entity.h"
#include "global_field_cell.h"
#include "global_field.h"

Entity::Entity(GlobalField* field, QObject* parent)
	: QObject{ parent }
	, m_field{ field }
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

void Entity::setPosition(int x, int y, float dx, float dy) {
	//qDebug("Squad position %d;%d %f;%f", x, y, dx, dy);
	if (m_position.x() != x || m_position.y() != y) {
		m_prev_position = m_position;
		auto cell = m_field->cell(m_position);
		if (cell) {
			cell->removeEntity(this);
		}
		cell = m_field->cell(x, y);
		if (cell) {
			cell->addEntity(this);
		}
	}

	m_position = QPoint{ x, y };
	m_offset = QPointF{ dx, dy };

	updateModelTransform();
}

void Entity::setPosition(QPointF value) {
	m_position.setX(value.x());
	m_position.setY(value.y());
	m_offset.setX(value.x() - m_position.x());
	m_offset.setY(value.y() - m_position.y());
	updateModelTransform();
}

void Entity::setPosition(int x, int y) {
	m_position = QPoint{ x, y };
	m_offset = QPointF{ 0, 0 };

	updateModelTransform();
}

void Entity::updateModelTransform() {

	if (!m_model)
		return;

	float size = GlobalField::cellSize();
	QMatrix m;
	m.translate((m_position.x() + m_offset.x()) * size, (m_position.y() + m_offset.y()) * size);
	m_model->setTransform(QTransform{ m });
	m_model->update();
}

void Entity::move(float dx, float dy) {
	float f_off_x = m_offset.x() + dx;
	float f_off_y = m_offset.y() + dy;
	int off_x = (int)f_off_x;
	int off_y = (int)f_off_y;
	int x = m_position.x() + off_x;
	int y = m_position.y() + off_y;
	dx = f_off_x - (float)off_x;
	dy = f_off_y - (float)off_y;

	if (dx > 0.5f) {
		x += 1;
		dx = dx - 1.0f;
	}
	if (dx < -0.5f) {
		x -= 1;
		dx = dx + 1.0f;
	}
	if (dy > 0.5f) {
		y += 1;
		dy = dy - 1.0f;
	}
	if (dy < -0.5f) {
		y -= 1;
		dy = dy + 1.0f;
	}

	setPosition(x, y, dx, dy);
}
