#include "db.h"
#include "window_type.h"

WindowType::WindowType()
{
    m_bounding_volume.reset(new BoundingVolume());
    m_bounding_volume->setWidth(120);
    m_bounding_volume->setHeight(100);
    m_bounding_volume->setDepth(30);
    m_name.reset(new UiText());
    m_name->setValue("Default window");
}

void WindowType::save() {
    m_bounding_volume->save();
    m_name->save();

    QSqlQuery q(GetDb());
    if (m_id == -1) {
        q.prepare("INSERT INTO window_types (bounding_volume, name_id) VALUES (:bounding_volume, name_id)");
        q.bindValue(":bounding_volume", m_bounding_volume->id());
        q.bindValue(":name_id", m_name->id());
        if (q.exec()) {
            bool ok;
            int v = q.lastInsertId().toInt(&ok);
            if (ok) {
                m_id = v;
                qDebug("Window type has been saved %d", m_id);
            } else {
                qDebug("Failed to save window type");
            }
        } else {
            qDebug("Failed execute window type save");
        }
    } else {
        q.prepare("UPDATE window_types SET bounding_volume=:bounding_volume, name_id=:name_id WHERE id=:id");
        q.bindValue(":bounding_volume", m_bounding_volume->id());
        q.bindValue(":name_id", m_name->id());
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Window type %d updated", m_id);
        } else {
            qDebug("Failed to update window type %d", m_id);
        }
    }
}

void WindowType::remove() {
    m_bounding_volume->remove();
    m_name->remove();

    if (m_id != -1) {
        QSqlQuery q(GetDb());
        q.prepare("DELETE FROM window_types WHERE id=:id");
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Window type %d has been removed", m_id);
        } else {
            qDebug("Failed to remove %d window type", m_id);
        }
    }
}

WindowType* WindowType::load(int id) {
    std::unique_ptr<WindowType> result{new WindowType};
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT bounding_volume, name_id FROM window_types WHERE id = :id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            int v = q.value("bounding_volume").toInt(&ok);
            if (ok) {
                auto volume = BoundingVolume::load(v);
                if (volume) {
                    result->m_bounding_volume.reset(volume);
                    qDebug("Bounding volume %d was loaded for window type %d", volume->id(), id);
                } else {
                    qDebug("Failed to load bounding volume for window type %d", id);
                    return nullptr;
                }
            } else {
                qDebug("Boundign volume for window type %d not found", id);
                return nullptr;
            }
            v = q.value("name_id").toInt(&ok);
            if (ok) {
                auto value = UiText::load(v);
                if (value) {
                    result->m_name.reset(value);
                    qDebug("Ui text %d was loaded for window type %d", value->id(), id);
                } else {
                    qDebug("Failed to load ui text for window type %d", id);
                    return nullptr;
                }
            } else {
                qDebug("Ui text for window type %d not found", id);
                return nullptr;
            }
        } else {
            qDebug("Window type %d not found", id);
            return nullptr;
        }
    } else {
        qDebug("Failed to execute window type load");
        return nullptr;
    }
    return result.release();
}
