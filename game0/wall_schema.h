#ifndef WALL_H
#define WALL_H

#include <QVector>
#include "point.h"
#include "window_schema.h"
#include "door_schema.h"
#include <memory>

class FloorSchema;
class WallSchema
{
public:
    WallSchema(FloorSchema* floor);
    ~WallSchema();

    void save();
    void remove();

    int id() const {
        return m_id;
    }

    Point* pointA() { return m_point_ref_a.get(); }
    const Point* pointA() const { return m_point_ref_a.get(); }

    Point* pointB() { return m_point_ref_b.get(); }
    Point* pointB() const { return m_point_ref_b.get(); }

    const FloorSchema* floor() const { return m_floor; }

    bool isInner() const { return m_inner; }

    void setInner(bool value) { m_inner = value; }

    int windowsCount() const {
        return m_window_schema.size();
    }

    int doorsCount() const {
        return m_door_schema.size();
    }

    WindowSchema* windowSchema(int index) {
        return m_window_schema.at(index);
    }

    const WindowSchema* windowSchema(int index) const {
        return m_window_schema.at(index);
    }

    DoorSchema* doorSchema(int index) {
        return m_door_schema.at(index);
    }

    const DoorSchema* doorSchema(int index) const {
        return m_door_schema.at(index);
    }

    void addWindowSchema(WindowSchema* value) {
        m_window_schema.push_back(value);
    }

    void addDoorSchema(DoorSchema* value) {
        m_door_schema.push_back(value);
    }

    void removeWindow(WindowSchema* window);
    void removeWindow(int index);
    void removeDoor(DoorSchema* door);
    void removeDoor(int index);

    static WallSchema* load(FloorSchema* floor, int id);

private:
    int m_id{-1};
    FloorSchema* m_floor{nullptr};
    bool m_inner{false};
    std::unique_ptr<Point> m_point_ref_a;
    std::unique_ptr<Point> m_point_ref_b;
    QVector<WindowSchema*> m_window_schema;
    QVector<DoorSchema*> m_door_schema;
};

#endif // WALL_H
