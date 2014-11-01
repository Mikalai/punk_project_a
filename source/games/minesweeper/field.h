#ifndef _H_FIELD
#define _H_FIELD

#include <vector>
#include <iosfwd>
#include <QtWidgets/qgraphicsscene.h>
#include <QtCore/qpoint.h>

class FieldCell;

class Field : public QGraphicsScene {
	Q_OBJECT;
	Q_PROPERTY(QPoint size MEMBER m_size);

public:
	Field(QObject* parent = nullptr);

	FieldCell* GetCell(int x, int y);

	void Save(std::ostream& stream);
	void Load(std::istream& stream);
	void Create(int width, int height, int mines_count);

	bool IsExploded() const {
		return m_exploded;
	}

	bool IsComplete() const;

signals:
	void explode();
	void started();
	void complete();
	void minesCountChanged(int value);

public slots:
	void explosion(FieldCell* cell);
	void opened(FieldCell* cell);
	void marked(bool value);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
private:
	QPoint m_size{ 10, 10 };
	int m_mines_count{ 10 };
	int m_mines_left{ 10 };
	int m_closed{ 100 };
	bool m_started{ false };
	bool m_exploded{ false };
	std::vector<std::vector<FieldCell*>> m_cells;
};

#endif	//	_H_FIELD