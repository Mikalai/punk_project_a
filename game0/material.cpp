#include "db.h"

#include "material.h"

Material::Material()
{
    m_name.reset(new UiText);
}

Material::~Material() {
}

void Material::save() {
    m_name->save();

    QSqlQuery q(GetDb());
    if (m_id == -1) {
        q.prepare("INSERT INTO materials (name_id) VALUES (:name_id)");
        q.bindValue(":name_id", m_name->id());
        if (q.exec()) {
            m_id = q.lastInsertId().toInt();
            qDebug("Temporary material created %d", m_id);
        } else {
            qDebug("Failed to create temporary material");
        }
    } else {
        q.prepare("UPDATE materials SET name_id=:name_id WHERE id=:id");
        q.bindValue(":name_id", m_name->id());
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Material %d has been updated", m_id);
        } else {
            qDebug("Failed to update material %d", m_id);
        }
    }
}

void Material::remove() {
    if (m_name.get())
        m_name->remove();

    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM materials WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Mateiral %id has been removed", m_id);
    } else {
        qDebug("Failed to remove mateiral %d ", m_id);
    }

    m_id = -1;
}

void Material::remove(int id) {
    QSqlQuery q(GetDb());

    q.prepare("DELETE FROM ui_strings WHERE id IN (SELECT name_id FROM materials WHERE materials.id=:id)");
    q.bindValue(":id", id);
    if (q.exec()) {
        qDebug("Ui name of material %d removed from db", id);
    } else {
        qDebug("Failed to remove ui name of material %d", id);
    }

    q.prepare("DELETE FROM materials WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        qDebug("Mateiral %id has been removed", id);
    } else {
        qDebug("Failed to remove mateiral %d ", id);
    }
}

void Material::setName(QString value) {
    if (m_name.get()) {
        m_name->setValue(value);
    }
}

QString Material::name() const {   
    return m_name->value();
}


Material* Material::load(int id) {
    QSqlQuery q(GetDb());
    q.prepare("SELECT name_id FROM materials WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            Material* result = new Material;
            result->m_id = id;
            int string_id = q.value(0).toInt(&ok);
            if (ok) {
                result->m_name.reset(UiText::load(string_id));
            } else {
                result->m_name.reset(new UiText);
            }
            return result;
        } else {
            qDebug("Failed to get material name %d", id);
        }
    } else {
        qDebug("Failed to fetch data about materia %d", id);
    }
    return nullptr;
}
