#ifndef FLOOR_SCHEMA_H
#define FLOOR_SCHEMA_H

#include "wall_schema.h"
#include <memory>
#include "point.h"
#include <QVector>

class BuildingSchema;

class FloorSchema
{
public:
    FloorSchema(BuildingSchema* building);
    ~FloorSchema();

    void save();
    void remove();

    int id() { return m_id; }

    WallSchema* wallSchema(int index) {
        return m_walls[index];
    }

    const WallSchema* wallSchema(int index) const {
        return m_walls[index];
    }

    int wallsCount() {
        return m_walls.size();
    }

    int number() const {
        return m_number;
    }

    void setNumber(int value) {
        m_number = value;
    }

    const BuildingSchema* building() const {
        return m_building;
    }

    void addWall(WallSchema* value) {
        m_walls.append(value);
    }

    static FloorSchema* load(BuildingSchema* building, int id);

private:
    int m_id{-1};
    BuildingSchema* m_building{nullptr};
    int m_number{-1};
    QVector<WallSchema*> m_walls;
};

#endif // FLOOR_SCHEMA_H
