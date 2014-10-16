#ifndef WINDOW_SCHEMA_H
#define WINDOW_SCHEMA_H

#include <memory>
#include "window_type.h"

class WallSchema;

class WindowSchema
{
public:
    WindowSchema(WallSchema* wall);

    void save();
    void remove();
    static WindowSchema* load(WallSchema* wall, int id);

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

    const WindowType* windowType() const {
        return m_type.get();
    }

    void setWindowType(int id) {
        m_type.reset(WindowType::load(id));
    }

private:
    int m_id{-1};
    WallSchema* m_wall{nullptr};
    float m_relative_position{0};
    std::unique_ptr<WindowType> m_type;
};

#endif // WINDOW_SCHEMA_H
