#include "field.h"
#include "spatial.h"

void Spatial::setPosition(int x, int y, float dx, float dy) {
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

	OnPositionChanged();
}

void Spatial::setPosition(QPointF value) {
	m_position.setX(value.x());
	m_position.setY(value.y());
	m_offset.setX(value.x() - m_position.x());
	m_offset.setY(value.y() - m_position.y());
	OnPositionChanged();
}

void Spatial::setPosition(int x, int y) {
	m_position = QPoint{ x, y };
	m_offset = QPointF{ 0, 0 };
	OnPositionChanged();
}

void Spatial::move(float dx, float dy) {
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
