#include <QtWidgets/qgraphicsitem.h>
#include "model_type.h"

class QImage;
class Squad;

class SquadGraphicsItem : public QGraphicsItem {
public:

	enum { Type = QGraphicsItem::UserType + (int)ModelType::Squad };
	int type() const override {
		return Type;
	}

	SquadGraphicsItem(Squad* squad, QGraphicsItem* parent = nullptr);
	QImage* GetSquadAvatar() const;
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	Squad* getSquad() const {
		return m_squad;
	}

protected:

	/*void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;*/
private:
	Squad* m_squad{ nullptr };
};