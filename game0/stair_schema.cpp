#include "db.h"
#include "building_schema.h"
#include "stair_schema.h"
#include "floor_schema.h"

StairsSchema::StairsSchema(BuildingSchema* building, FloorSchema* bottom, FloorSchema* top)
    : m_bottom_floor{bottom}
    , m_top_floor{top}
    , m_building{building}
{
    m_type.reset(new StairsType);
    m_position.reset(new Point);
}

void StairsSchema::save() {

    m_position->save();

    QSqlQuery q(GetDb());
    if (m_id == -1) {
        q.prepare("INSERT INTO stair_schemas (bottom_floor_id, top_floor_id, position_id, stairs_type_id, building_id) VALUES (:bottom_floor_id, :top_floor_id, :position_id, :stairs_type_id, :building_id)");
        q.bindValue(":bottom_floor_id", m_bottom_floor->id());
        q.bindValue(":top_floor_id", m_top_floor->id());
        q.bindValue(":position_id", m_position->id());
        q.bindValue(":stairs_type_id", m_type->id());
        q.bindValue(":building_id", m_building->id());
        if (q.exec()) {
            bool ok;
            int v = q.lastInsertId().toInt(&ok);
            if (ok) {
                m_id = v;
                qDebug("Stairs schema %d has been saved", m_id);
            } else {
                qDebug("Failed to insert new stairs schema in db");
            }
        } else {
            qDebug("Failed to save new stairs schema");
        }
    } else {
        q.prepare("UPDATE stair_schemas SET bottom_floor_id=:bottom_floor_id, top_floor_id=:top_floor_id, position_id=:position_id, stairs_type_id=:stairs_type_id, building_id=:building_id WHERE id=:id");
        q.bindValue(":bottom_floor_id", m_bottom_floor->id());
        q.bindValue(":top_floor_id", m_top_floor->id());
        q.bindValue(":position_id", m_position->id());
        q.bindValue(":stairs_type_id", m_type->id());
        q.bindValue(":building_id", m_building->id());
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Stairs schema %d was updated", m_id);
        } else {
            qDebug("Failed to update stairs schema %d", m_id);
        }
    }
}

void StairsSchema::remove() {
    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM stair_schemas WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Stairs schema %d has been removed from db", m_id);
    } else {
        qDebug("Failed to remove stairs schema %d from db", m_id);
    }
}

StairsSchema* StairsSchema::load(BuildingSchema* building, FloorSchema* bottom, FloorSchema* top, int id) {
    std::unique_ptr<StairsSchema> result(new StairsSchema(building, bottom, top));
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT position_id, stairs_type_id FROM stair_schemas WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            auto v = q.value("position_id").toInt(&ok);
            if (ok) {
                auto value = Point::load(v);
                if (value) {
                    result->m_position.reset(value);
                    qDebug("Stairs schema %d has %d position", id, result->m_position->id());
                } else {
                    qDebug("Failed to position for stairs schema %d", id);
                    return nullptr;
                }
            } else {
                qDebug("Failed to load relative position for stairs schema %d", id);
                return nullptr;
            }
            auto i = q.value("stairs_type_id").toInt(&ok);
            if (ok) {
                auto value = StairsType::load(i);
                if (value) {
                    result->m_type.reset(value);
                    qDebug("Stairs schema %d has %d stairs type", id, value->id());
                } else {
                    qDebug("Failed to load stairs type for stairs schema %d. Use default.", id);
                }
            }
        } else {
            qDebug("Stairs schema %d not found", id);
            return nullptr;
        }
    } else {
        qDebug("Failed to load stairs schema %d", id);
        return nullptr;
    }
    return result.release();
}
