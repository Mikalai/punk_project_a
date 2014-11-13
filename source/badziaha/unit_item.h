#ifndef _H_UNIT_ITEM
#define _H_UNIT_ITEM

#include <QtWidgets/qgraphicsitem.h>

class Unit;

class UnitItem : public QGraphicsItem {
public:
	UnitItem(Unit* unit, QGraphicsItem* item);
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
	Unit* m_unit{ nullptr };
};
#endif	//	_H_UNIT_ITEM