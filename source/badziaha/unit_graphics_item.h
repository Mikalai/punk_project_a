#ifndef _H_UNIT_GRAPHICS_ITEM
#define _H_UNIT_GRAPHICS_ITEM

#include <QtWidgets/qgraphicsitem.h>
#include "resources.h"
#include "model_type.h"

template<class T, ModelType MT >
class UnitGraphicsItem : public QGraphicsItem {
public:

	enum { Type = QGraphicsItem::UserType + (int)MT };

	UnitGraphicsItem(T* unit, QGraphicsItem* parent = nullptr)
		: QGraphicsItem{ parent }
		, m_unit{ unit } {

	}

	QRectF boundingRect() const override {
		auto image = Resources::instance()->getCityImage();
		float w = image->width();
		float h = image->height();
		return QRectF{ -w / 2.0, -h / 2.0, w, h };
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		auto image = Resources::instance()->getModelImage(MT);
		float w = image->width();
		float h = image->height();
		painter->drawImage(QPointF{ -w / 2, -h / 2 }, *image);
	}

	T* getUnit() {
		return m_unit;
	}

	int type() const override {
		return Type;
	}

private:
	T* m_unit{ nullptr };
};

#endif	//	_H_UNIT_GRAPHICS_ITEM