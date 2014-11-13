#include <QtWidgets/qgraphicsview.h>
#include "unit.h"
#include "keys.h"
#include "character.h"
#include "unit_model.h"
#include "local_field.h"

Unit::Unit(LocalField* field, Character* character, int squad_id, QObject* parent)
	: QObject{ parent }
	, m_character{ character }
	, m_squad_id{ squad_id }
	, m_field{ field }
{
	m_model = new UnitModel{ this, nullptr };
	m_model->setZValue(1);
	updateTransform();
}

bool Unit::isHumanControl() const {
	return m_character->isHumanControl();
}

QMatrix Unit::getTransform() const {
	QMatrix m;
	m.rotate(m_rotation * 180 / 3.1415926536f);
	m.translate(m_position.x(), m_position.y());
	return m;
}

void Unit::update() {
	TimeDependent::update();
	auto dt = getTimeStep();

	if (isHumanControl()) {
		auto keys = Keys::instance();

		QPointF dir{ 0, 0 };
		if (keys->keyboard(Qt::Key_A))
			dir.setX(dir.x() - 1);
		if (keys->keyboard(Qt::Key_D))
			dir.setX(dir.x() + 1);
		if (keys->keyboard(Qt::Key_W))
			dir.setY(dir.y() + 1);
		if (keys->keyboard(Qt::Key_S))
			dir.setY(dir.y() - 1);

		auto l = dir.manhattanLength();
		if (l > 1e-3f) {
			dir = dir / dir.manhattanLength();

			QMatrix rm;
			rm.rotate(rotation() * 180 / 3.1415f);
			dir = dir * rm;

			m_position += dir * dt * 1.4f;

			updateTransform();
		}
	}
}

void Unit::updateTransform() {
	if (!m_model)
		return;

	float size = 1;// LocalField::cellSize();
	QMatrix m;
	m.rotate(m_rotation * 180 / 3.1592653);
	m.translate(m_position.x() * size, m_position.y() * size);
	m_model->setTransform(QTransform{ m });
	m_model->update();

	if (isHumanControl()) {
		for (auto view : field()->views()) {
			view->centerOn(m_model);
		}
	}
}

void Unit::setPosition(QPointF value) {
	m_position = value;
	updateTransform();
}