#ifndef _H_LOCAL_FIELD_ITEM
#define _H_LOCAL_FIELD_ITEM

#include "model_type.h"
#include <QtWidgets/qgraphicsitem.h>
#include "fwd_items.h"
#include "entity.h"

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

class LocalFieldItem : public QGraphicsItem {
public:
	
	LocalFieldItem(ItemPtr item, QGraphicsItem* parent);
	const Item* item() const { return m_item.get(); }
	ItemPtr removeItem() { return std::move(m_item); }

	//	QGraphicsItem
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

	enum { Type = QGraphicsItem::UserType + (int)(ModelType::LocalFieldItem) };

	int type() const override {
		return Type;
	}	

private:
	ItemPtr m_item;
};

#endif	//	_H_LOCAL_FIELD_ITEM