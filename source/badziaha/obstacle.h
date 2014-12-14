#ifndef _H_OBSTACLE
#define _H_OBSTACLE

#include "entity.h"

class Obstacle : public Entity {
public:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
	QRectF boundingRect() const override;
};

#endif	//	_H_OBSTACLE