#ifndef BUILDING_SCHEMA_H
#define BUILDING_SCHEMA_H

#include <QString>
#include <memory>
#include "polygon.h"
#include "ui_text.h"
#include "wall_material.h"
#include "roof_material.h"
#include "floor_schema.h"
#include "stair_schema.h"
#include "point.h"

class BuildingSchema
{
public:
    BuildingSchema();
    ~BuildingSchema();

    void save();
    void remove();
    static BuildingSchema* load(int id);
    static void removeTrash();
    static void remove(int id);
    void clear();

    UiText* name() {
        return m_name.get();
    }

    const UiText* name() const {
        return m_name.get();
    }

    int floorsCount() const {
        return m_floors_count;
    }

    void setFloorsCount(int value);

    FloorSchema* floorSchema(int index) {
        if (index < m_floors.size())
            return m_floors[index];
        return nullptr;
    }

    const FloorSchema* floorSchema(int index) const {
        return m_floors[index];
    }

    FloorSchema* floorSchemaById(int id) {
        auto it = std::find_if(m_floors.begin(), m_floors.end(), [&id] (FloorSchema* s) { return s->id() == id; });
        if (it != m_floors.end())
            return *it;
        return nullptr;
    }

    WallMaterial* wallMaterial() {
        return m_wall_material.get();
    }

    const WallMaterial* wallMaterial() const {
        return m_wall_material.get();
    }

    void setWallMaterial(int id) {
        m_wall_material.reset(WallMaterial::load(id));
    }

    RoofMaterial* roofMaterial() {
        return m_roof_material.get();
    }

    const RoofMaterial* roofMaterial() const {
        return m_roof_material.get();
    }

    void setRoofMaterial(int id) {
        m_roof_material.reset(RoofMaterial::load(id));
    }

    Polygon* polygon() {
        return m_polygon.get();
    }

    const Polygon* polygon() const {
        return m_polygon.get();
    }

    void setPolygon(int id) {
        m_polygon.reset(Polygon::load(id));
    }

    void setRefPoint(int id) {
        m_ref_point.reset(Point::load(id));
    }

    const Point* refPoint() const {
        return m_ref_point.get();
    }

    Point* refPoint() {
        return m_ref_point.get();
    }

    int id() {
        return m_id;
    }

    int stairsCount() const {
        return m_stairs.size();
    }

    StairsSchema* stairsSchema(int index) {
        return m_stairs.at(index);
    }

    const StairsSchema* stairsSchema(int index) const {
        return m_stairs.at(index);
    }

    void addStairs(StairsSchema* value) {
        m_stairs.append(value);
    }

    FloorSchema* nextFloor(FloorSchema* floor);
    FloorSchema* prevFloor(FloorSchema* floor);

    void updateWalls();

    static bool isUniqueName(QString value);

private:
    int m_id{-1};
    std::unique_ptr<UiText> m_name;
    std::unique_ptr<WallMaterial> m_wall_material;
    std::unique_ptr<RoofMaterial> m_roof_material;
    std::unique_ptr<Polygon> m_polygon;
    std::unique_ptr<Point> m_ref_point;
    int m_floors_count{0};
    QVector<FloorSchema*> m_floors;
    QVector<StairsSchema*> m_stairs;
};

#endif // BUILDING_SCHEMA_H
