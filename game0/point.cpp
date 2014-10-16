#include <memory>
#include "db.h"
#include "point.h"

Point::Point() {
}

Point::~Point() {
}

void Point::remove() {
    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM points WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Point %d has been removed from db", m_id);
    } else {
        qDebug("Failed to remove %d point from db", m_id);
    }
}

void Point::save() {
    QSqlQuery q(GetDb());
    if (m_id == -1) {
        QSqlQuery q(GetDb());
        q.prepare("INSERT INTO points (x, y, z, w) VALUES (:x, :y, :z, :w)");
        q.bindValue(":x", m_x);
        q.bindValue(":y", m_y);
        q.bindValue(":z", m_z);
        q.bindValue(":w", m_w);
        if (q.exec()) {
            m_id = q.lastInsertId().toInt();
            qDebug("Temporary point created %d", m_id);
        } else {
            qDebug("Failed to create temporary point");
        }
    } else {
        q.prepare("UPDATE points SET x=:x, y=:y, z=:z, w=:w WHERE id=:id");
        q.bindValue(":x", m_x);
        q.bindValue(":y", m_y);
        q.bindValue(":z", m_z);
        q.bindValue(":w", m_w);
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Point %d has been updated with (%f, %f, %f, %f)", m_id, m_x, m_y, m_z, m_w);
        } else {
            qDebug("Failed to update Point %d with (%f, %f, %f, %f)", m_id, m_x, m_y, m_z, m_w);
        }
    }
}

Point* Point::load(int id) {
    std::unique_ptr<Point> result{new Point};
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT x, y, z, w FROM points WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            bool ok;                        
            float v = q.value(0).toFloat(&ok);
            if (ok)
                result->m_x = v;
            v = q.value(1).toFloat(&ok);
            if (ok)
                result->m_y = v;
            v = q.value(2).toFloat(&ok);
            if (ok)
                result->m_z = v;
            v = q.value(3).toFloat(&ok);
            if (ok)
                result->m_w = v;
            qDebug("Point %d created %f, %f, %f, %f", result->m_id, result->m_x, result->m_y, result->m_z, result->m_w);            
        }
    } else {
        qDebug("Failed to get point %d", id);
        return nullptr;
    }
    return result.release();
}
