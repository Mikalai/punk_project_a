#include "db.h"
#include "floor_schema.h"
#include "building_schema.h"

FloorSchema::FloorSchema(BuildingSchema* building)
    : m_building{building}
{

}

FloorSchema::~FloorSchema() {
    while (!m_walls.empty()) {
        delete m_walls.back();
        m_walls.pop_back();
    }
}

void FloorSchema::remove() {
    for (int i = 0; i < m_walls.size(); ++i) {
        m_walls[i]->remove();
    }

    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM floor_schemas WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Floor %d has been removed", m_id);
    } else {
        qDebug("Failed to remove floor %d", m_id);
    }
}

void FloorSchema::save() {    

    if (m_id == -1) {
        QSqlQuery q(GetDb());
        q.prepare("INSERT INTO floor_schemas (building_schema_id, floor_number) VALUES (:building_schema_id, :floor_number)");
        q.bindValue(":building_schema_id", m_building->id());
        q.bindValue(":floor_number", m_number);
        if (q.exec()) {
            m_id = q.lastInsertId().toInt();
            qDebug("Temporary floor %d has been created for building %d", m_id, m_building->id());
        } else {
            qDebug("Failed to create temporary floor for schema building %d", m_building->id());
        }
    } else {
        QSqlQuery q(GetDb());
        q.prepare("UPDATE floor_schemas SET floor_number=:floor_number, building_schema_id=:building_schema_id WHERE id=:id");
        q.bindValue(":floor_number", m_number);
        q.bindValue(":building_schema_id", m_building->id());
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Floor %d updated", m_id);
        } else {
            qDebug("Failed to update floor %d", m_id);
        }
    }

    for (int i = 0, max_i = m_walls.size(); i < max_i; ++i) {
        m_walls[i]->save();
    }
}

FloorSchema* FloorSchema::load(BuildingSchema *building, int id) {
    std::unique_ptr<FloorSchema> result{new FloorSchema(building)};
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT floor_number FROM floor_schemas WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            auto number = q.value(0).toInt(&ok);
            if (ok) {
                result->m_number = number;
                qDebug("Floor %d has %d number", id, result->m_number);
            } else {
                qDebug("Failed to get floor %d number", id);
            }
        } else {
            qDebug("No floor number data for floor %d", id);
            return nullptr;
        }
    } else {
        qDebug("Failed to get floor number");
        return nullptr;
    }

    q.prepare("SELECT id FROM wall_schemas WHERE floor_id=:floor_id");
    q.bindValue(":floor_id", id);
    if (q.exec()) {
        while (q.next()) {
            bool ok;
            int v = q.value(0).toInt(&ok);
            if (ok) {
                WallSchema* wall = WallSchema::load(result.get(), v);
                qDebug("Wall %d found on the floor %d", wall->id(), id);
                result->addWall(wall);
            } else {
                qDebug("Failed to get wall for floor %d", id);
            }
        }
    } else {
        qDebug("Failed to fetch wall for floor %d", id);
        return nullptr;
    }
    return result.release();
}
