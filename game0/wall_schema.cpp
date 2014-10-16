#include "db.h"
#include "wall_schema.h"
#include "floor_schema.h"

WallSchema::WallSchema(FloorSchema* floor)
    : m_floor{floor}
{
    m_point_ref_a.reset(new Point);
    m_point_ref_b.reset(new Point);

}

WallSchema::~WallSchema() {
    while (!m_window_schema.empty()) {
        delete m_window_schema.back();
        m_window_schema.pop_back();
    }
    while (!m_door_schema.empty()) {
        delete m_door_schema.back();
        m_door_schema.pop_back();
    }
}

void WallSchema::remove() {

    m_point_ref_a->remove();
    m_point_ref_b->remove();

    for (auto& w : m_window_schema) {
        w->remove();
    }

    for (auto& d : m_door_schema) {
        d->remove();
    }

    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM wall_schemas WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Wall %d has been removed", m_id);
    } else {
        qDebug("Failed to remove wall %d", m_id);
    }
}

void WallSchema::save() {
    m_point_ref_a->save();
    m_point_ref_b->save();

    QSqlQuery q(GetDb());
    if (m_id== -1) {
        QSqlQuery q(GetDb());
        q.prepare("INSERT INTO wall_schemas (floor_id, point_a_id, point_b_id) VALUES (:floor_id, :point_a_id, :point_b_id)");
        q.bindValue(":floor_id", m_floor->id());
        q.bindValue(":point_a_id", m_point_ref_a->id());
        q.bindValue(":point_b_id", m_point_ref_b->id());
        if (q.exec()) {
            m_id = q.lastInsertId().toInt();
            qDebug("Temporary wall %d created for floor %d", m_id, m_floor->id());
        } else {
            qDebug("Failed to create temporary wall for floor %d", m_floor->id());
        }
    }
    else {
        q.prepare("UPDATE wall_schemas SET floor_id=:floor_id, point_a_id=:point_a_id, point_b_id=:point_b_id, inner=:inner WHERE id = :id");
        q.bindValue(":floor_id", m_floor->id());
        q.bindValue(":point_a_id", m_point_ref_a->id());
        q.bindValue(":point_b_id", m_point_ref_b->id());
        q.bindValue(":inner", m_inner);
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Wall %d has been updated for floor %d", m_id, m_floor->id());
        } else {
            qDebug("Failed to commit wall %d for floor %d", m_id, m_floor->id());
        }
    }

    for (auto& w : m_window_schema) {
        w->save();
    }

    for (auto& d : m_door_schema) {
        d->save();
    }
}

WallSchema* WallSchema::load(FloorSchema *floor, int id) {
    std::unique_ptr<WallSchema> result{new WallSchema(floor)};
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT floor_id, point_a_id, point_b_id, inner FROM wall_schemas WHERE id = :id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {            
            bool ok;
            int v;
            v = q.value(0).toInt(&ok);
            v = q.value(1).toInt(&ok);
            if (ok) {
                result->m_point_ref_a.reset(Point::load(v));
                qDebug("Wall %d has %d ref point a", id, result->m_point_ref_a->id());
            } else {
                result->m_point_ref_a.reset(new Point);
                qDebug("Wall %d has bad point ref a", id);
            }
            v = q.value(2).toInt(&ok);
            if (ok) {
                result->m_point_ref_b.reset(Point::load(v));
                qDebug("Wall %d has %d ref point b", id, result->m_point_ref_b->id());
            } else {
                result->m_point_ref_b.reset(new Point);
                qDebug("Wall %d has bad point ref b", id);
            }
            result->m_inner = q.value(3).toBool();            
        }
    } else {
        qDebug("Failed to get data for wall %d", id);
        return nullptr;
    }

    //  load windows
    q.prepare("SELECT id FROM window_schemas WHERE window_schemas.wall_id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        while (q.next()) {
            bool ok;
            int v = q.value("id").toInt(&ok);
            if (ok) {
                auto value = WindowSchema::load(result.get(), v);
                if (value) {
                    result->addWindowSchema(value);
                    qDebug("Window schema %d loaded for wall %d", value->id(), id);
                } else {
                    qDebug("Failed to load window schema %d for wall %d", v, id);
                    return nullptr;
                }
            } else {
                qDebug("Failed to get window schema for wall %d", id);
                return nullptr;
            }
        }
    } else {
        qDebug("Failed to fetch windows schemas for wall schema %d", id);
        return nullptr;
    }

    //  load doors
    q.prepare("SELECT id FROM door_schemas WHERE door_schemas.wall_id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        while (q.next()) {
            bool ok;
            int v = q.value("id").toInt(&ok);
            if (ok) {
                auto value = DoorSchema::load(result.get(), v);
                if (value) {
                    result->addDoorSchema(value);
                    qDebug("Door schema %d loaded for wall %d", value->id(), id);
                } else {
                    qDebug("Failed to load door schema %d for wall %d", v, id);
                    return nullptr;
                }
            } else {
                qDebug("Failed to get door schema for wall %d", id);
                return nullptr;
            }
        }
    } else {
        qDebug("Failed to fetch doors schemas for wall schema %d", id);
        return nullptr;
    }
    return result.release();
}

void WallSchema::removeWindow(WindowSchema* window) {
    auto it = std::find(m_window_schema.begin(), m_window_schema.end(), window);
    if (it == m_window_schema.end())
        return;
    (*it)->remove();
    delete (*it);
    m_window_schema.erase(it);
}

void WallSchema::removeWindow(int index) {
    removeWindow(m_window_schema.at(index));
}

void WallSchema::removeDoor(DoorSchema *door) {
    auto it = std::find(m_door_schema.begin(), m_door_schema.end(), door);
    if (it == m_door_schema.end())
        return;
    (*it)->remove();
    delete (*it);
    m_door_schema.erase(it);
}

void WallSchema::removeDoor(int index) {
    removeDoor(m_door_schema.at(index));
}
