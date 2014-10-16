#ifndef POLYGON_H
#define POLYGON_H

#include <QPolygon>
#include "point.h"

class Polygon
{
public:
    Polygon();
    ~Polygon();

    void remove();
    void save();

    const QPolygonF toPolygonF() const;

    int id() const {
        return m_id;
    }

    int pointCount() {
        return m_points.size();
    }

    Point* point(int index) {
        return m_points.at(index);
    }

    const Point* point(int index) const {
        return m_points.at(index);
    }

    void addPoint(Point* point) {
        m_points.append(point);
    }

    static Polygon* load(int id);

private:
    int m_id{-1};
    QVector<Point*> m_points;
};

#endif // POLYGON_H
