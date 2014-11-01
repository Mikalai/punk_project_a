#ifndef _H_CITY_GRAPHICS_ITEM
#define _H_CITY_GRAPHICS_ITEM

#include <QtWidgets/qgraphicsitem.h>
#include "model_type.h"

class City;

class CityGraphicsItem : public QGraphicsItem {
public:

	enum { Type = QGraphicsItem::UserType + (int)ModelType::City };

	CityGraphicsItem(City* city, QGraphicsItem* parent = nullptr);
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	City* getCity() {
		return m_city;
	}

	int type() const override {
		return Type;
	}

private:
	City* m_city{ nullptr };
};

#endif	//	_H_CITY_GRAPHICS_ITEM