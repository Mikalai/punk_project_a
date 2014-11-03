#include <QtWidgets/qgraphicssceneevent.h>
#include "city_widget.h"
#include "../global_field.h"
#include "../buildings.h"
#include "../city.h"
#include "../city_task.h"

CityWidget::CityWidget(QWidget* parent)
	: QWidget{ parent }
	, ui{ new Ui::CityWidget }
{
	ui->setupUi(this);
}

void CityWidget::setCity(City* city) {
	qDebug(__FUNCTION__);
	m_city = city;
	setVisible(m_city != nullptr);
	if (m_city) {
		ui->m_name->setText(city->name());
	}
}

void CityWidget::selectFieldCell(QGraphicsSceneMouseEvent* event, GlobalFieldCell* cell) {
	qDebug(__FUNCTION__);

	if (!m_city)
		return;

	if (m_new_task.get() && m_new_task->needInput()) {
		if (event->button() == Qt::MouseButton::LeftButton) {
			m_new_task->selectCell(cell);
			if (!m_new_task->needInput())
				m_city->addTask(m_new_task.release());
		}
	}
}

void CityWidget::buildRoad() {
	qDebug(__FUNCTION__);

	if (!m_city)
		return;

	m_new_task.reset(new BuildRoad{ m_city});
}

void CityWidget::buildSawmill() {	
	qDebug(__FUNCTION__);

	if (!m_city)
		return;

	auto mill = new SawMill{ m_city->field(), m_city->field() };

	m_new_task.reset(new Build{ m_city, mill });
}