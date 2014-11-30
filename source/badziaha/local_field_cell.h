#ifndef _H_LOCAL_FIELD_CELL
#define _H_LOCAL_FIELD_CELL

#include "field.h"
#include "enum_helper.h"
#include "model_type.h"

class GlobalFieldCell;
class QWidget;
class QStyleOptionGraphicsItem;
class QPainter;

class LocalFieldCell : public FieldCell {
public:
	
	enum { Type = QGraphicsItem::UserType + (int)(ModelType::LocalFieldCell) };
	
	int type() const override {
		return Type;
	}

	LocalFieldCell(const QPointF& global_position, QGraphicsItem* parent = nullptr);

	//	QGraphicsItem
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	void setPosition(QPoint value);
	void setGlobalCell(GlobalFieldCell* cell);
	GlobalFieldCell* globalCell();
	
	void add(QPointF local_position, ItemPtr value);
	bool hasItem(const Item* value);
	ItemPtr remove(const Item* value);

	const std::vector<const Item*> items() const;

	LocalField* field() const;
	GlobalFieldCell* globalFieldCell() const;

	void update() override;

private:
	QBrush getGroundBrush() const;
};

#endif	//	_H_LOCAL_FIELD_CELL