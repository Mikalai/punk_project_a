#ifndef _H_CITY_WIDGET
#define _H_CITY_WIDGET

#include <QtWidgets/qwidget.h>
#include "city_widget.ui.h"

class City;

class CityWidget : public QWidget {
	Q_OBJECT;
public:
	CityWidget(QWidget* parent = nullptr);

public slots:
	void setCity(City* city);

private:
	City* m_city{ nullptr };
	Ui::CityWidget* ui{ nullptr };
};
#endif	//	_H_CITY_WIDGET