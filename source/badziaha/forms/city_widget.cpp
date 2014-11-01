#include "city_widget.h"
#include "../city.h"

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
}