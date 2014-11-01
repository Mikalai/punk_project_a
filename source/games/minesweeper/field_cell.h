#ifndef _H_FIELD_CELL
#define _H_FIELD_CELL

#include <QtWidgets/qgraphicsitem.h>
#include <QtCore/qpoint.h>

class Field;

class FieldCell : public QObject, public QGraphicsItem {
	Q_PROPERTY(QPoint index MEMBER m_index);
	Q_OBJECT
public:
	FieldCell(int x, int y, Field* field);
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	void SetMine(bool value) {
		m_has_mine = value;
	}

	bool HasMine() const {
		return m_has_mine;
	}

	void Open();

	bool IsOpened() const {
		return m_opened;
	}

	bool IsMarked() const {
		return m_marked;
	}

	void Mark();

	void Save(std::ostream& stream);
	void Load(std::istream& stream);

	/*void Select(bool value) {
		m_selected = value;
	}

	bool IsSelected() const {
		return m_selected;
	}*/

signals:
	void explode(FieldCell* cell);
	void opened(FieldCell* cell);
	void marked(bool value);

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	int GetNeighbourMinesCount() const;
	int GetMarkedMinesCount() const;

private:
	Field* m_field{ nullptr };
	QPoint m_index;
	bool m_mouse_in{ false };
	bool m_opened{ false };
	bool m_marked{ false };
	static const int m_width{ 40 };
	bool m_has_mine{ false };
	//bool m_selected{ false };
};

#endif	//	_H_FIELD_CELL