#include "db.h"
#include "wall_schema.h"
#include "window_schema.h"

WindowSchema::WindowSchema(WallSchema* wall)
    : m_wall{wall}
{
    m_type.reset(new WindowType);
}

void WindowSchema::save() {
    QSqlQuery q(GetDb());
    if (m_id == -1) {
        q.prepare("INSERT INTO window_schemas (wall_id, relative_position, window_type_id) VALUES (:wall_id, :relative_position, :window_type_id)");
        q.bindValue(":wall_id", m_wall->id());
        q.bindValue(":relative_position", m_relative_position);
        q.bindValue(":window_type_id", m_type->id());
        if (q.exec()) {
            bool ok;
            int v = q.lastInsertId().toInt(&ok);
            if (ok) {
                m_id = v;
                qDebug("Window schema %d has been saved", m_id);
            } else {
                qDebug("Failed to insert new window schema in db");
            }
        } else {
            qDebug("Failed to save new window schema");
        }
    } else {
        q.prepare("UPDATE window_schemas SET wall_id=:wall_id, relative_position=:relative_position, window_type_id=:window_type_id WHERE id=:id");
        q.bindValue(":wall_id", m_wall->id());
        q.bindValue(":relative_position", m_relative_position);
        q.bindValue(":window_type_id", m_type->id());
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Window schema %d was updated", m_id);
        } else {
            qDebug("Failed to update window schema %d", m_id);
        }
    }
}

void WindowSchema::remove() {
    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM window_schemas WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Window schema %d has been removed from db", m_id);
    } else {
        qDebug("Failed to remove window schema %d from db", m_id);
    }
}

WindowSchema* WindowSchema::load(WallSchema* wall, int id) {
    std::unique_ptr<WindowSchema> result(new WindowSchema(wall));
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT relative_position, window_type_id FROM window_schemas WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            auto v = q.value("relative_position").toFloat(&ok);
            if (ok) {
                result->m_relative_position = v;
                qDebug("Window schema %d has %f relative position", id, result->m_relative_position);
            } else {
                qDebug("Failed to load relative position for window schema %d", id);
                return nullptr;
            }
            auto i = q.value("window_type_id").toInt(&ok);
            if (ok) {
                auto value = WindowType::load(i);
                if (value) {
                    result->m_type.reset(value);
                    qDebug("Window schema %d has %d window type", id, value->id());
                } else {
                    qDebug("Failed to load window type for window schema %d. Use default.", id);
                }
            }
        } else {
            qDebug("Window schema %d not found", id);
            return nullptr;
        }
    } else {
        qDebug("Failed to load window schema %d", id);
        return nullptr;
    }
    return result.release();
}
