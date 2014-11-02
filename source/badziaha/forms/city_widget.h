#ifndef _H_CITY_WIDGET
#define _H_CITY_WIDGET

#include <memory>
#include <QtWidgets/qwidget.h>
#include "city_widget.ui.h"

class CityTask;
class City;
class GlobalFieldCell;
class QGraphicsSceneMouseEvent; 

class CityWidget : public QWidget {
	Q_OBJECT;
public:
	CityWidget(QWidget* parent = nullptr);

public slots:
	void setCity(City* city);
	void selectFieldCell(QGraphicsSceneMouseEvent* event, GlobalFieldCell* cell);
	void buildRoad();
	void buildSawmill();

private:
	City* m_city{ nullptr };
	Ui::CityWidget* ui{ nullptr };
	std::unique_ptr<CityTask> m_new_task{ nullptr };
};
#endif	//	_H_CITY_WIDGET