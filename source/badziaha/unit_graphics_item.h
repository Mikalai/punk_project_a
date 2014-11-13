#ifndef _H_Character_GRAPHICS_ITEM
#define _H_Character_GRAPHICS_ITEM

#include <QtGui/qpainter.h>
#include <QtWidgets/qgraphicsitem.h>
#include "resources.h"
#include "model_type.h"

template<class T, ModelType MT >
class CharacterGraphicsItem : public QGraphicsItem {
public:

	enum { Type = QGraphicsItem::UserType + (int)MT };

	CharacterGraphicsItem(T* Character, QGraphicsItem* parent = nullptr)
		: QGraphicsItem{ parent }
		, m_Character{ Character } {

	}

	QRectF boundingRect() const override {
		auto image = Resources::instance()->getCityImage();
		float w = image->width();
		float h = image->height();
		return QRectF{ -w / 2.0, -h / 2.0, w, h };
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		auto image = Resources::instance()->modelImage(MT);
		float w = image->width();
		float h = image->height();
		painter->drawImage(QPointF{ -w / 2, -h / 2 }, *image);
	}

	T* getCharacter() {
		return m_Character;
	}

	int type() const override {
		return Type;
	}

private:
	T* m_Character{ nullptr };
};

#endif	//	_H_Character_GRAPHICS_ITEM