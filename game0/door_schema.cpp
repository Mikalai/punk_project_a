#include "db.h"
#include "wall_schema.h"
#include "door_schema.h"

DoorSchema::DoorSchema(WallSchema* wall)
    : m_wall{wall}
{
    m_type.reset(new DoorType);
}

void DoorSchema::save() {
    QSqlQuery q(GetDb());
    if (m_id == -1) {
        q.prepare("INSERT INTO door_schemas (wall_id, relative_position, door_type_id) VALUES (:wall_id, :relative_position, :door_type_id)");
        q.bindValue(":wall_id", m_wall->id());
        q.bindValue(":relative_position", m_relative_position);
        q.bindValue(":door_type_id", m_type->id());
        if (q.exec()) {
            bool ok;
            int v = q.lastInsertId().toInt(&ok);
            if (ok) {
                m_id = v;
                qDebug("Door schema %d has been saved", m_id);
            } else {
                qDebug("Failed to insert new door schema in db");
            }
        } else {
            qDebug("Failed to save new door schema");
        }
    } else {
        q.prepare("UPDATE door_schemas SET wall_id=:wall_id, relative_position=:relative_position, door_type_id=:door_type_id WHERE id=:id");
        q.bindValue(":wall_id", m_wall->id());
        q.bindValue(":relative_position", m_relative_position);
        q.bindValue(":door_type_id", m_type->id());
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Door schema %d was updated", m_id);
        } else {
            qDebug("Failed to update door schema %d", m_id);
        }
    }
}

void DoorSchema::remove() {
    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM door_schemas WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Door schema %d has been removed from db", m_id);
    } else {
        qDebug("Failed to remove door schema %d from db", m_id);
    }
}

DoorSchema* DoorSchema::load(WallSchema* wall, int id) {
    std::unique_ptr<DoorSchema> result(new DoorSchema(wall));
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT relative_position, door_type_id FROM door_schemas WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            auto v = q.value("relative_position").toFloat(&ok);
            if (ok) {
                result->m_relative_position = v;
                qDebug("Door schema %d has %f relative position", id, result->m_relative_position);
            } else {
                qDebug("Failed to load relative position for door schema %d", id);
                return nullptr;
            }
            auto i = q.value("door_type_id").toInt(&ok);
            if (ok) {
                auto value = DoorType::load(i);
                if (value) {
                    result->m_type.reset(value);
                    qDebug("Door schema %d has %d door type", id, value->id());
                } else {
                    qDebug("Failed to load door type for door schema %d. Use default.", id);
                }
            }
        } else {
            qDebug("Door schema %d not found", id);
            return nullptr;
        }
    } else {
        qDebug("Failed to load door schema %d", id);
        return nullptr;
    }
    return result.release();
}
