#include "db.h"
#include "door_type.h"

DoorType::DoorType()
{
    m_bounding_volume.reset(new BoundingVolume());
    m_bounding_volume->setWidth(100);
    m_bounding_volume->setHeight(200);
    m_bounding_volume->setDepth(30);
    m_name.reset(new UiText());
    m_name->setValue("Default door");
}

void DoorType::save() {
    m_bounding_volume->save();
    m_name->save();

    QSqlQuery q(GetDb());
    if (m_id == -1) {
        q.prepare("INSERT INTO door_types (bounding_volume, name_id) VALUES (:bounding_volume, name_id)");
        q.bindValue(":bounding_volume", m_bounding_volume->id());
        q.bindValue(":name_id", m_name->id());
        if (q.exec()) {
            bool ok;
            int v = q.lastInsertId().toInt(&ok);
            if (ok) {
                m_id = v;
                qDebug("Window type has been saved %d", m_id);
            } else {
                qDebug("Failed to save door type");
            }
        } else {
            qDebug("Failed execute door type save");
        }
    } else {
        q.prepare("UPDATE door_types SET bounding_volume=:bounding_volume, name_id=:name_id WHERE id=:id");
        q.bindValue(":bounding_volume", m_bounding_volume->id());
        q.bindValue(":name_id", m_name->id());
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Window type %d updated", m_id);
        } else {
            qDebug("Failed to update door type %d", m_id);
        }
    }
}

void DoorType::remove() {
    m_bounding_volume->remove();
    m_name->remove();

    if (m_id != -1) {
        QSqlQuery q(GetDb());
        q.prepare("DELETE FROM door_types WHERE id=:id");
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Window type %d has been removed", m_id);
        } else {
            qDebug("Failed to remove %d door type", m_id);
        }
    }
}

DoorType* DoorType::load(int id) {
    std::unique_ptr<DoorType> result{new DoorType};
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT bounding_volume, name_id FROM door_types WHERE id = :id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            int v = q.value("bounding_volume").toInt(&ok);
            if (ok) {
                auto volume = BoundingVolume::load(v);
                if (volume) {
                    result->m_bounding_volume.reset(volume);
                    qDebug("Bounding volume %d was loaded for door type %d", volume->id(), id);
                } else {
                    qDebug("Failed to load bounding volume for door type %d", id);
                    return nullptr;
                }
            } else {
                qDebug("Boundign volume for door type %d not found", id);
                return nullptr;
            }
            v = q.value("name_id").toInt(&ok);
            if (ok) {
                auto value = UiText::load(v);
                if (value) {
                    result->m_name.reset(value);
                    qDebug("Ui text %d was loaded for door type %d", value->id(), id);
                } else {
                    qDebug("Failed to load ui text for door type %d", id);
                    return nullptr;
                }
            } else {
                qDebug("Ui text for door type %d not found", id);
                return nullptr;
            }
        } else {
            qDebug("Window type %d not found", id);
            return nullptr;
        }
    } else {
        qDebug("Failed to execute door type load");
        return nullptr;
    }
    return result.release();
}
