#ifndef STAIR_SCHEMA_H
#define STAIR_SCHEMA_H

#include <memory>
#include "point.h"
#include "stairs_type.h"

class BuildingSchema;
class FloorSchema;

class StairsSchema
{
public:
    StairsSchema(BuildingSchema* building, FloorSchema* bottom, FloorSchema* top);

    void save();
    void remove();
    static StairsSchema* load(BuildingSchema* building, FloorSchema* bottom, FloorSchema* top, int id);

    int id() const {
        return m_id;
    }

    FloorSchema* bottomFloor() {
        return m_bottom_floor;
    }

    const FloorSchema* bottomFloor() const {
        return m_bottom_floor;
    }

    FloorSchema* topFloor() {
        return m_top_floor;
    }

    const FloorSchema* topFloor() const {
        return m_top_floor;
    }


    const Point* position() const {
        return m_position.get();
    }

    Point* position() {
        return m_position.get();
    }

    const StairsType* stairsType() const {
        return m_type.get();
    }

    void setStairsType(int id) {
        m_type.reset(StairsType::load(id));
    }

    BuildingSchema* buildingSchema() {
        return m_building;
    }

    const BuildingSchema* buildingSchema() const {
        return m_building;
    }

private:
    int m_id{-1};
    FloorSchema* m_bottom_floor{nullptr};
    FloorSchema* m_top_floor{nullptr};
    BuildingSchema* m_building{nullptr};
    std::unique_ptr<Point> m_position;
    std::unique_ptr<StairsType> m_type;
};


#endif // STAIR_SCHEMA_H
