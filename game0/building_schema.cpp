#include <QVariant>
#include <QSqlQuery>
#include "db.h"
#include "floor_schema.h"
#include "building_schema.h"

BuildingSchema::BuildingSchema()
    : m_id{-1}
{  
    m_name.reset(new UiText());
    //m_wall_material.reset(new WallMaterial());
    //m_roof_material.reset(new RoofMaterial());
    m_polygon.reset(new Polygon());
    m_ref_point.reset(new Point);

    for (int i = 0; i < m_floors_count; ++i) {
        auto floor = new FloorSchema(this);
        m_floors.push_back(floor);
    }
}

BuildingSchema::~BuildingSchema() {
    while (!m_floors.empty()) {
        delete m_floors.back();
        m_floors.pop_back();
    }
    while (!m_stairs.empty()) {
        delete m_stairs.back();
        m_stairs.pop_back();
    }
}

void BuildingSchema::save() {
    m_name->save();
    if (m_wall_material.get()) {
        m_wall_material->save();
    }
    if (m_roof_material.get()) {
        m_roof_material->save();
    }
    m_polygon->save();

    m_ref_point->setPointF(*m_polygon->point(0));
    m_ref_point->save();

    QSqlQuery q(GetDb());
    if (m_id == -1) {

        q.prepare("INSERT INTO building_schemas (name_id, floors_count, polygon_id, walls_material_id, roof_material_id) VALUES (:name_id, :floors_count, :polygon_id, NULL, NULL)");
        q.bindValue(":name_id", m_name->id());
        q.bindValue(":floors_count", m_floors_count);
        q.bindValue(":polygon_id", m_polygon->id());

        if (q.exec()) {
            m_id = q.lastInsertId().toInt();
            qDebug("Create new empty building schema %d", m_id);
        }
        else {
            qDebug("Failed to create new building schema");
        }

    } else {
        q.prepare("UPDATE building_schemas SET floors_count=:floors_count, name_id=:name_id, polygon_id=:polygon_id, walls_material_id=:walls_material_id, roof_material_id=:roof_material_id, point_ref_id=:point_ref_id WHERE id=:id");
        q.bindValue(":floors_count", m_floors_count);
        q.bindValue(":name_id", m_name->id());
        q.bindValue(":polygon_id", m_polygon->id());
        if (m_wall_material.get())
            q.bindValue(":walls_material_id", m_wall_material->id());
        else
            q.bindValue(":walls_material_id", "null");
        if (m_roof_material.get())
            q.bindValue(":roof_material_id", m_roof_material->id());
        else
            q.bindValue(":roof_material_id", "null");

        q.bindValue(":point_ref_id", m_ref_point->id());
        q.bindValue(":id", m_id);

        if (q.exec()) {
            qDebug("Floors count changed to %d", m_floors_count);
        } else {
            qDebug("Failed to update floors count to %d", m_floors_count);
        }
    }

    for (int i = 0, max_i = m_floors.size(); i < max_i; ++i) {
        m_floors[i]->save();
    }

    for (int i = 0, max_i = m_stairs.size(); i < max_i; ++i) {
        m_stairs[i]->save();
    }
}

void BuildingSchema::remove() {

    if (m_name)
        m_name->remove();
    if (m_wall_material)
        m_wall_material->remove();
    if (m_roof_material)
        m_roof_material->remove();
    if (m_polygon)
        m_polygon->remove();
    if (m_ref_point)
        m_ref_point->remove();

    for (int i = 0, max_i = m_floors.size(); i < max_i; ++i) {
        m_floors[i]->remove();
    }

    for (int i = 0, max_i = m_stairs.size(); i < max_i; ++i) {
        m_stairs[i]->remove();
    }

    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM building_schemas WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Schema %d delete from db", m_id);
    } else {
        qDebug("Failed to delete schema %d", m_id);
    }

    m_id = -1;
}

bool BuildingSchema::isUniqueName(QString value) {
    QSqlQuery q(GetDb());
    q.prepare("SELECT ui_strings.id FROM ui_strings, building_schemas WHERE ui_strings.id = building_schemas.name_id AND ui_strings.value = :value");
    q.bindValue(":value", value);
    if (q.exec()) {
        if (q.next())
            return false;
        else
            return true;
    }
    return true;
}

void BuildingSchema::updateWalls() {
    while (!m_floors.empty()) {
        m_floors.back()->remove();
        delete m_floors.back();
        m_floors.pop_back();
    }

    m_ref_point->setPointF(*m_polygon->point(0));
    QPointF ref_point = *m_ref_point;
    for (int i = 0; i < m_floors_count; ++i) {
        FloorSchema* floor_schema = new FloorSchema(this);
        QPolygonF polygon = m_polygon->toPolygonF();
        for (int j = 0, max_j = polygon.size(); j < max_j; ++j) {
            QPointF p1 = polygon[j] - ref_point;
            QPointF p2 = polygon[(j+1) % max_j] - ref_point;
            WallSchema* wall_schema = new WallSchema(floor_schema);
            wall_schema->pointA()->setPointF(p1);
            wall_schema->pointB()->setPointF(p2);
            wall_schema->setInner(false);
            floor_schema->addWall(wall_schema);
        }
        m_floors.push_back(floor_schema);
    }
}

BuildingSchema* BuildingSchema::load(int id) {
    std::unique_ptr<BuildingSchema> result(new BuildingSchema);
    QSqlQuery q(GetDb());
    q.prepare("SELECT name_id, floors_count, polygon_id, walls_material_id, roof_material_id, point_ref_id FROM building_schemas WHERE id = :id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            result->m_id = id;
            bool ok;
            int name_id = q.value(0).toInt(&ok);
            if (ok) {
                auto name = UiText::load(name_id);
                if (name) {
                    result->m_name.reset(name);
                    qDebug("Name id %d fetched for schema %d", name_id, id);
                } else {
                    qDebug("Name id %d was not loaded", name_id);
                    return nullptr;
                }

            } else {
                qDebug("Failed to fetch name id for scheam %d", id);
                return nullptr;
            }

            int floors_count = q.value(1).toInt(&ok);
            if (ok) {
                result->m_floors_count = floors_count;
                qDebug("Schema %d has %d floors", id, result->m_floors_count);
            } else {
                qDebug("Failed to fetch floor count for scheam %d", id);
                return nullptr;
            }

            int polygon_id = q.value(2).toInt(&ok);
            if (ok) {
                auto polygon = Polygon::load(polygon_id);
                if (polygon) {
                    result->m_polygon.reset(polygon);
                    qDebug("Schema %d has %d polygon", id, polygon_id);
                } else {
                    qDebug("Polygon %d was not loaded", polygon_id);
                }
            } else {
                qDebug("Failed to fetch polygon id for schema %d", id);
                return nullptr;
            }

            if (!q.value(3).isNull()) {
                int wall_material = q.value(3).toInt(&ok);
                if (ok) {
                    result->m_wall_material.reset(WallMaterial::load(wall_material));
                    qDebug("Schema %d has %d wall material", id, wall_material);
                } else {
                    qDebug("Failed to fetch wall material id for schema %d", id);
                    //return nullptr;
                }
            } else {
                qDebug("No wall material for schema %d" , id);
            }


            if (!q.value(4).isNull()) {
                int roof_material = q.value(4).toInt(&ok);
                if (ok) {
                    result->m_roof_material.reset(RoofMaterial::load(roof_material));
                    qDebug("Schema %d has %d wall material", id, roof_material);
                } else {
                    qDebug("Failed to fetch roof material id for schema %d", id);
                    //return nullptr;
                }
            } else {
                qDebug("No roof material for schame %d", id);
            }

            if (!q.value(5).isNull()) {
                int point_id = q.value(5).toInt(&ok);
                if (ok) {
                    auto ref_point = Point::load(point_id);
                    if (ref_point) {
                        result->m_ref_point.reset(ref_point);
                        qDebug("Schema %d has %d ref point", id, point_id);
                    } else {
                        qDebug("Failed to load ref point %d for schema %d", point_id, id);
                        return nullptr;
                    }
                } else {
                    qDebug("Failed to fetch ref point id for schema %d", id);
                    return nullptr;
                }
            } else {
                result->m_ref_point.reset(new Point());
                qDebug("No roof material for schema %d, created new %d", id, result->m_ref_point->id());
            }

        } else {
            qDebug("No building schema found with id %d", id);
            return nullptr;
        }
    }

    q.prepare("SELECT floor_schemas.id FROM floor_schemas WHERE floor_schemas.building_schema_id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        while (q.next()) {
            bool ok;
            int floor_id = q.value(0).toInt(&ok);
            if (ok) {
                auto floor = FloorSchema::load(result.get(), floor_id);
                if (floor) {
                    result->m_floors.push_back(floor);
                    qDebug("Floor %d loaded for schema %d", floor_id, id);
                }
                else {
                    qDebug("Floor %d was not loaded", floor_id);
                    return nullptr;
                }
            } else {
                qDebug("Failed to get floor id schema %d", id);
                return nullptr;
            }
        }
    } else {
        qDebug("Failed to get floor infor for schema %d", id);
        return nullptr;
    }

    q.prepare("SELECT id, bottom_floor_id, top_floor_id FROM stair_schemas WHERE building_id=:building_id");
    q.bindValue(":building_id", id);
    if (q.exec()) {
        while (q.next()) {
            FloorSchema* bottom_floor;
            FloorSchema* top_floor;
            bool ok;
            int bottom_floor_id = q.value(":bottom_floor_id").toInt(&ok);
            if (ok) {
                bottom_floor = result->floorSchemaById(bottom_floor_id);
                if (!bottom_floor) {
                    qDebug("Floor schema %d not found in the building %d", bottom_floor_id, id);
                    return nullptr;
                }
            } else {
                qDebug("Failed to get id of the bottom floor for building %d", id);
                return nullptr;
            }
            int top_floor_id = q.value(":top_floor_id").toInt(&ok);
            if (ok) {
                top_floor = result->floorSchemaById(top_floor_id);
                if (!top_floor) {
                    qDebug("Floor schema %d not found in the building %d", top_floor_id, id);
                    return nullptr;
                }
            } else {
                qDebug("Failed to get id of the top floor for building %d", id);
                return nullptr;
            }
            int stairs_id = q.value(":id").toInt(&ok);
            if (ok) {
                auto value = StairsSchema::load(result.get(), bottom_floor, top_floor, stairs_id);
                if (value) {
                    result->addStairs(value);
                    qDebug("Stairs %d loaded for building %d", value->id(), id);
                }
            } else {
                qDebug("Failed to get id of the stairs for building %d", id);
                return nullptr;
            }
        }
    } else {
        qDebug("Failed to get stairs for building %d", id);
    }
    return result.release();
}

void BuildingSchema::setFloorsCount(int value) {
    if (m_floors_count == value)
        return;

    for (int i = 0, max_i = m_floors.size(); i < max_i; ++i) {
        m_floors[i]->remove();;
        delete m_floors[i];
    }
    m_floors.clear();
    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM floor_schemas WHERE building_schema_id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("All floors has been removed for building %d", m_id);
    } else {
        qDebug("Failed to remove all floors building %d", m_id);
    }

    m_floors_count = value;
    for (int i = 0; i < value; ++i) {
        auto floor = new FloorSchema(this);
        floor->setNumber(i);
        m_floors.push_back(floor);
    }
}

FloorSchema* BuildingSchema::nextFloor(FloorSchema* floor) {
    int num = floor->number();
    for (auto f : m_floors) {
        if (f->number() == num+1)
            return f;
    }
    return nullptr;
}

FloorSchema* BuildingSchema::prevFloor(FloorSchema* floor) {
    int num = floor->number();
    for (auto f: m_floors) {
        if (f->number() == num-1)
            return f;
    }
    return nullptr;
}
