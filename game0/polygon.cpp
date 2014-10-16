#include <QSqlQuery>
#include <QVariant>
#include <memory>
#include "db.h"
#include "polygon.h"

Polygon::Polygon()
{}

Polygon::~Polygon() {
    while (!m_points.empty()) {
        delete m_points.back();
        m_points.pop_back();
    }
}


void Polygon::save() {

    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM polygons WHERE id=:id");
    q.bindValue(":id", m_id);
    if (!q.exec())
        return;
    for (int i = 0; i < m_points.size(); ++i) {
        m_points[i]->save();
        if (i == 0 && m_id == -1) {
            q.prepare("INSERT INTO polygons (point_id) VALUES (:point_id)");
            q.bindValue(":point_id", m_points[i]->id());
            m_id = q.lastInsertId().toInt();
        } else {
            q.prepare("INSERT INTO polygons (id, point_id) VALUES (:id, :point_id)");
            q.bindValue(":id", m_id);
            q.bindValue(":point_id", m_points[i]->id());
        }
        if (q.exec()) {
            qDebug("Point %d added to polygon %d", m_points[i]->id(), m_id);
        } else {
            qDebug("Failed to add point %d to polygon", m_points[i]->id());
        }
    }
}

void Polygon::remove() {
    while (!m_points.empty()) {
        m_points.back()->remove();
        delete m_points.back();
        m_points.pop_back();
    }

    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM polygons WHERE id = :id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("References on points have been removed from %d polygon", m_id);
    } else {
        qDebug("Failed to remove references on points from %d polygon", m_id);
    }
}

Polygon* Polygon::load(int id) {
    std::unique_ptr<Polygon> result{new Polygon};
    result->m_id = id;
    QSqlQuery q(GetDb());
    q.prepare("SELECT point_id FROM polygons WHERE id = :id");
    q.bindValue(":id", id);
    if (q.exec()) {        
        while (q.next()) {
            bool ok;
            int point_id = q.value(0).toInt(&ok);
            if (!ok) {
                qDebug("Failed to get point id");
                return nullptr;
            } else {
                Point* point = Point::load(point_id);
                result->addPoint(point);
            }
        }        
    } else {
        qDebug("Failed to get points of the polygon %d", id);
        return nullptr;
    }
    return result.release();
}

const QPolygonF Polygon::toPolygonF() const {
    QPolygonF p;
    for (int i = 0; i < m_points.size(); ++i) {
        p.append(*m_points[i]);
    }
    return p;
}
