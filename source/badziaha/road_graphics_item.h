#ifndef _H_ROAD_GRAPHICS_ITEM
#define _H_ROAD_GRAPHICS_ITEM

#include <QtWidgets/qgraphicsitem.h>
#include "model_type.h"

class Road;

class RoadGraphicsItem : public QGraphicsItem {
public:
	enum { Type = QGraphicsItem::UserType + (int)ModelType::Road };

	RoadGraphicsItem(Road* value, QGraphicsItem* parent = nullptr);
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	void* getRoad() {
		return m_road;
	}

	int type() const override {
		return Type;
	}

	void updateBoundingBox();

	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
private:
	QRectF m_bbox;
	Road* m_road{ nullptr };
};

#endif	//	_H_ROAD_GRAPHICS_ITEM