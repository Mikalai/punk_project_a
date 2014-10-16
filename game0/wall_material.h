#ifndef WALL_MATERIAL_H
#define WALL_MATERIAL_H

#include <memory>
#include "material.h"
#include <QAbstractTableModel>

class WallMaterial
{
public:
    WallMaterial();
    ~WallMaterial();

    void save();
    void remove();

    Material* material() {
        return m_material.get();
    }

    const Material* material() const {
        return m_material.get();
    }

    int id() {
        return m_id;
    }

    static QAbstractTableModel* getAll(QObject* owner);

    static WallMaterial* load(int index);
private:
    int m_id{-1};
    bool m_temp{true};
    std::unique_ptr<Material> m_material;
};

#endif // WALL_MATERIAL_H
