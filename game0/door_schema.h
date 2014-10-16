#ifndef DOOR_SCHEMA_H
#define DOOR_SCHEMA_H

#include <memory>
#include "door_type.h"

class WallSchema;

class DoorSchema
{
public:
    DoorSchema(WallSchema* wall);

    void save();
    void remove();
    static DoorSchema* load(WallSchema* wall, int id);

    int id() const {
        return m_id;
    }

    WallSchema* wall() {
        return m_wall;
    }

    const WallSchema* wall() const {
        return m_wall;
    }

    float relativePosition() const {
        return m_relative_position;
    }

    void setRelativePosition(float value) {
        m_relative_position = value;
    }

    const DoorType* windowType() const {
        return m_type.get();
    }

    void setDoorType(int id) {
        m_type.reset(DoorType::load(id));
    }

private:
    int m_id{-1};
    WallSchema* m_wall{nullptr};
    float m_relative_position{0};
    std::unique_ptr<DoorType> m_type;
};

#endif // DOOR_SCHEMA_H
