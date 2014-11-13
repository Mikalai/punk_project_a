#ifndef _H_Character_MODEL
#define _H_Character_MODEL

#include <QtWidgets/qgraphicsitem.h>

enum class UnitModelType {
	Ranger
};

class Unit;

class UnitModel : public QGraphicsItem {
public:
	UnitModel(Unit* unit, QGraphicsItem* parent = nullptr);

	QRectF boundingRect() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	UnitModel* clone() const;

	Unit* unit() { return m_unit; }
private:
	Unit* m_unit{ nullptr };
};

extern UnitModel* model(UnitModelType type);

#endif	//	_H_Character