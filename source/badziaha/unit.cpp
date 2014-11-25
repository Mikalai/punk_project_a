#include <QtWidgets/qgraphicsview.h>
#include "unit.h"
#include "keys.h"
#include "character.h"
#include "unit_model.h"
#include "local_field.h"

Unit::Unit(LocalField* field, Character* character, int squad_id, QGraphicsItem* parent)
	: QGraphicsItem{ parent }
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
	//	position in the renderer is represented in cm
	m.translate(m_position.x() * 100.0f, m_position.y()*100.0f);
	m.rotate(m_rotation * 180 / 3.1415926536f);
	return m;
}

void Unit::update() {
	TimeDependent::update();
	auto dt = getTimeStep();

	if (isHumanControl()) {
		auto keys = Keys::instance();

		QPointF dir{ 0, 0 };
		if (keys->keyboard(Qt::Key_W))
			dir.setX(dir.x() + 1);
		if (keys->keyboard(Qt::Key_S))
			dir.setX(dir.x() - 1);
		if (keys->keyboard(Qt::Key_D))
			dir.setY(dir.y() + 1);
		if (keys->keyboard(Qt::Key_A))
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

	//	position in the renderer is in cm
	float size = 100.f;// LocalField::cellSize();
	QMatrix m;	
	m.translate(m_position.x() * size, m_position.y() * size);
	m.rotate(m_rotation * 180 / 3.1592653);
	m_model->setTransform(QTransform{ m });
	m_model->update();

	if (isHumanControl()) {
		field()->centerOn(m_model->scenePos());
	}	
}

void Unit::setPosition(QPointF value) {
	m_position = value;
	updateTransform();
}

void Unit::setTarget(const QPointF& value) {
	auto m_target = value;
	auto dir = m_target - position()*100.0f;
	dir = dir / dir.manhattanLength();
	m_rotation = atan2f(dir.y(), dir.x());
	updateTransform();
}

QRectF Unit::boundingRect() const {
	return m_character->model()->boundingRect();
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->drawRect(boundingRect());
	//painter->drawImage(0, 0, m_character->model())
}