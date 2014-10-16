#ifndef ROOF_MATERIAL_H
#define ROOF_MATERIAL_H

#include <memory>
#include "material.h"
#include <QAbstractTableModel>

class RoofMaterial
{
public:
    RoofMaterial();
    ~RoofMaterial();

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

    static RoofMaterial* load(int id);
    static QAbstractTableModel* getAll(QObject* owner);

private:
    int m_id{-1};
    std::unique_ptr<Material> m_material;
};

#endif // ROOF_MATERIAL_H
