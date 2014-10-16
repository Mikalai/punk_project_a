#include <memory>
#include "db.h"
#include "bounding_volume.h"

BoundingVolume::BoundingVolume()
{
}

void BoundingVolume::save() {
    QSqlQuery q(GetDb());

    if (m_id == -1) {
        q.prepare("INSERT INTO bounding_volumes (width, height, depth) VALUES (:width, :height, :depth)");
        q.bindValue(":width", m_width);
        q.bindValue(":height", m_height);
        q.bindValue(":depth", m_depth);
        if (q.exec()) {
            bool ok;
            auto v = q.lastInsertId().toInt(&ok);
            if (ok) {
                m_id = v;
                qDebug("Bounding volume %d (%f, %f, %f) has been saved", m_id, m_width, m_height, m_depth);
            } else {
                qDebug("Failed to save bounding volume (%f, %f, %f) has been saved", m_width, m_height, m_depth);
            }
        } else {
            qDebug("Failed to save bounding bolume");
        }
    } else {
        q.prepare("UPDATE boundign_volumes SET width=:width, height=:height, depth=:depth WHERE id=:id");
        q.bindValue(":width", m_width);
        q.bindValue(":height", m_height);
        q.bindValue(":depth", m_depth);
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Bounding volume %d (%f, %f, %f) has been saved", m_id, m_width, m_height, m_depth);
        } else {
            qDebug("Failed to save bounding bolume");
        }
    }
}

void BoundingVolume::remove() {
    if (m_id != -1) {
        QSqlQuery q(GetDb());
        q.prepare("DELETE FROM bounding_volumes WHERE id=:id");
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Bounding volume %d has been removed", m_id);
        } else {
            qDebug("Failed to remove bounding volume %d", m_id);
        }
    }
}

BoundingVolume* BoundingVolume::load(int id) {
    std::unique_ptr<BoundingVolume> result{new BoundingVolume};
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT width, height, depth FROM bounding_volumes WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;
            result->m_width = q.value("width").toFloat(&ok);
            if (ok) {
                qDebug("Bounding volume %d has %f width", id, result->m_width);
            } else {
                qDebug("Failed to load bounding volume %d width", id);
                return nullptr;
            }
            result->m_height = q.value("height").toFloat(&ok);
            if (ok) {
                qDebug("Bounding volume %d has %f height", id, result->m_height);
            } else {
                qDebug("Failed to load bounding volume %d height", id);
                return nullptr;
            }
            result->m_depth = q.value("depth").toFloat(&ok);
            if (ok) {
                qDebug("Bounding volume %d has %f depth", id, result->m_depth);
            } else {
                qDebug("Failed to load bounding volume %d depth", id);
                return nullptr;
            }
        } else {
            qDebug("%d bounding volume not found", id);
            return nullptr;
        }
    } else {
        qDebug("Failed to load %d bounding volume", id);
        return nullptr;
    }
    return result.release();
}
