#include <QSqlTableModel>
#include <QVariant>
#include "db.h"

#include "roof_material.h"

RoofMaterial::RoofMaterial()
{
    m_material.reset(new Material);
}

RoofMaterial::~RoofMaterial() {
}

void RoofMaterial::save() {
    m_material->save();

    QSqlQuery q(GetDb());
    if (m_id == -1) {
        q.prepare("INSERT INTO roof_materials (material_id) VALUES (:material_id)");
        q.bindValue(":material_id", m_material->id());
        if (q.exec()) {
            bool ok;
            m_id = q.lastInsertId().toInt(&ok);
            if (ok) {
                qDebug("Temporary roof material created %d", m_id);
            }else {
                qDebug("Failed to create temporary material");
            }
        } else {
            qDebug("Failed to create temporary material");
        }
    } else {
        q.prepare("UPDATE roof_materials SET material_id=:material_id WHERE id=:id");
        q.bindValue(":material_id", m_material->id());
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("roof material %d updated", m_id);
        } else {
            qDebug("Failed to update material %d", m_id);
        }
    }
}

QAbstractTableModel* RoofMaterial::getAll(QObject* owner) {
    auto model = new QSqlQueryModel(owner);
    model->setQuery("SELECT roof_materials.id, ui_strings.value, ui_strings.id FROM ui_strings, roof_materials WHERE roof_materials.name_id = ui_strings.id", GetDb());
    return model;
}

void RoofMaterial::remove() {
    if (m_material.get())
        m_material->remove();

    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM roof_materials WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("roof mateiral %id has been removed", m_id);
    } else {
        qDebug("Failed to remove roof mateiral %d ", m_id);
    }
    m_id = -1;
}


RoofMaterial* RoofMaterial::load(int id) {
    QSqlQuery q(GetDb());
    q.prepare("SELECT material_id FROM roof_materials WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            int material_id = q.value(0).toInt(&ok);
            RoofMaterial* result = new RoofMaterial;
            if (ok) {
                result->m_material.reset(Material::load(material_id));
            } else {
                result->m_material.reset(new Material);
            }
            return result;
        } else {
            qDebug("Failed to get roof material %d", id);
        }
    } else {
        qDebug("Failed to fetch data about material %d", id);
    }
    return nullptr;
}
