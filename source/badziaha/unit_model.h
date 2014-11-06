#ifndef _H_UNIT_MODEL
#define _H_UNIT_MODEL

#include <QtWidgets/qgraphicsitem.h>

enum class UnitModelType {
	Ranger
};

class UnitModel : public QGraphicsItem {
public:
	UnitModel(QGraphicsItem* parent = nullptr);

	QRectF boundingRect() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	UnitModel* clone() const;
private:
};

extern UnitModel* model(UnitModelType type);

#endif	//	_H_UNIT