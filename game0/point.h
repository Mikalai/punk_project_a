#ifndef POINT_H
#define POINT_H

#include <QPointF>

class Point
{
public:
    Point();
    ~Point();

    void save();
    void remove();

    operator const QPointF() {
        return QPointF(m_x, m_y);
    }

    float x() { return m_x; }
    float y() { return m_y; }
    float z() { return m_z; }
    float w() { return m_w; }

    void setX(float value) { m_x = value; }
    void setY(float value) { m_y = value; }
    void setZ(float value) { m_z = value; }
    void setW(float value) { m_w = value; }

    void setPointF(const QPointF& value) { m_x = value.x(); m_y = value.y(); }
    int id() { return m_id; }

    static Point* load(int id);

private:
    int m_id {-1};
    float m_x{0};
    float m_y{0};
    float m_z{0};
    float m_w{1};    
};

#endif // POINT_H
