#ifndef _H_CITY_WIDGET
#define _H_CITY_WIDGET

#include <memory>
#include <QtWidgets/qwidget.h>
#include "city_widget.ui.h"

class CityTask;
class City;
class GlobalFieldCell;
class QGraphicsSceneMouseEvent; 
class QTimer;

class CityWidget : public QWidget {
	Q_OBJECT;
public:
	CityWidget(QWidget* parent = nullptr);

public slots:
	void setCity(City* city);
	void selectFieldCell(QGraphicsSceneMouseEvent* event, GlobalFieldCell* cell);
	void buildRoad();
	void buildSawmill();
	void updateModel();

private:
	QTimer* m_timer{ nullptr };
	City* m_city{ nullptr };
	Ui::CityWidget* ui{ nullptr };
	std::unique_ptr<CityTask> m_new_task{ nullptr };
};

class CityModel : public QAbstractItemModel {
	Q_OBJECT

public slots:
	void refresh();

public:

	CityModel(City* value, QObject* parent);
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &child) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	City* m_city{ nullptr };
	const QModelIndex Resources;
	const QModelIndex Roads;
	const QModelIndex Characters;
};
#endif	//	_H_CITY_WIDGET