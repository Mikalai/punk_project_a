#ifndef STAIRS_TYPE_H
#define STAIRS_TYPE_H

#include <memory>
#include "bounding_volume.h"
#include "ui_text.h"

class StairsType
{
public:
    StairsType();

    void save();
    void remove();
    static StairsType* load(int id);

    BoundingVolume* boundingVolume() {
        return m_bounding_volume.get();
    }

    const BoundingVolume* boundingVolume() const {
        return m_bounding_volume.get();
    }

    UiText* name() {
        return m_name.get();
    }

    const UiText* name() const {
        return m_name.get();
    }

    int id() const {
        return m_id;
    }

private:
    int m_id{-1};
    std::unique_ptr<BoundingVolume> m_bounding_volume;
    std::unique_ptr<UiText> m_name;
};
#endif // STAIRS_TYPE_H
