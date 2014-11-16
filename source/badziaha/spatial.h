#ifndef _H_SPATIAL
#define _H_SPATIAL

#include <QtCore/qpoint.h>

class Field;

class Spatial {
public:

	Spatial(Field* field)
		: m_field{ field }
	{}

	void setPosition(QPointF value);
	void setPosition(int x, int y);
	void setPosition(int x, int y, float dx, float dy);

	const QPoint& position() const {
		return m_position;
	}

	const QPoint& prevPosition() const {
		return m_prev_position;
	}

	const QPointF fullPosition() const {
		return QPointF{ m_position.x() + m_offset.x(), m_position.y() + m_offset.y() };
	}

	void move(float dx, float dy);

	Field* field() {
		return m_field;
	}

	const Field* field() const {
		return m_field;
	}

protected:
	virtual void OnPositionChanged() {}

private:
	Field* m_field{ nullptr };
	QPoint m_prev_position{ 0, 0 };
	QPoint m_position{ 0, 0 };
	QPointF m_offset{ 0, 0 };
};

#endif	