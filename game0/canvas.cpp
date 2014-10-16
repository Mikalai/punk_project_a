#include <QSqlQuery>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsItem>
#include "canvas.h"
#include "db.h"

Canvas::Canvas(QWidget *parent) :
    QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setMouseTracking(true);
    setScene(m_scene);
    m_cursor = m_scene->addEllipse(-5, -5, 10, 10);
    m_contour_brush = QBrush(Qt::SolidPattern);
    m_contour_pen = QPen(m_contour_brush, 15.0f, Qt::SolidLine);
    m_contour_pen.setCosmetic(true);
    m_contour_pen.setWidth(5);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    qDebug("Mouse press");
    QPolygonF scene_offset = mapToScene(QRect(event->pos() - QPoint(5, 5), QSize(10,10)));
    QPointF cur = mapToScene(event->pos());
    qDebug("Current scene position (%f;%f)", cur.x(), cur.y());
    roundPoint(cur);
    qDebug("Current scene position (%f;%f)", cur.x(), cur.y());
    qDebug("Current screen position (%d;%d)", event->pos().x(), event->pos().y());
    qDebug("Scene offset (%f;%f)", scene_offset.boundingRect().width(), scene_offset.boundingRect().height());

    if (event->button() == Qt::RightButton) {
        qDebug("Finish drawing contour");
        m_has_prev_fixed_point = false;
        if (m_current_line) {
            m_scene->removeItem(m_current_line);
            m_current_line = nullptr;
        }
        return;
    }
    if (m_mode == CanvasMode::DrawPolygon) {
        m_current_line = m_scene->addLine(QLineF(cur, cur));
        m_current_line->setPen(m_contour_pen);
        m_has_prev_fixed_point = true;
        m_cursor->setPos(cur);
        m_prev_fixed_point = cur;
    }
    else if (m_mode == CanvasMode::MovePoint) {
        QList<QGraphicsItem *> items = m_scene->items(scene_offset, Qt::IntersectsItemBoundingRect);
        if (items.empty()) {
            qDebug("Nothing selected");
        }
        else {
            qDebug("Selected %d items", items.size());
            m_current_lines.clear();
            m_line_index.clear();
            for (QGraphicsItem* item : items) {
                QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(item);
                if (line) {
                    m_current_lines.push_back(line);
                    auto dst1 = (line->line().p1() - cur).manhattanLength();
                    auto dst2 = (line->line().p2() - cur).manhattanLength();
                    if (dst1 < dst2) {
                        m_line_index.push_back(0);  //  move p1
                    } else {
                        m_line_index.push_back(1);  //  move p2
                    }
                }
            }
            if (m_current_lines.size() == 2) {
                qDebug("Selection influence 2 lines");
            }
        }
    }
    else if (m_mode == CanvasMode::RemovePoint) {
        QList<QGraphicsItem *> items = m_scene->items(scene_offset, Qt::IntersectsItemBoundingRect);
        while (!items.empty()) {
            m_scene->removeItem(items.back());
            items.pop_back();
        }
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
    m_prev_fixed_point = cur;
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    //qDebug("Mouse move");
    auto cur = mapToScene(event->pos());
    roundPoint(cur);
    auto delta = cur - m_prev;
    if (event->buttons() & Qt::LeftButton) {
        if (m_mode == CanvasMode::MovePoint) {
            qDebug("Move line points on offset %f,%f", delta.x(), delta.y());
            for (int i = 0, max_i = m_current_lines.size(); i < max_i; ++i) {
                QGraphicsLineItem* line = m_current_lines[i];
                int point = m_line_index[i];
                auto l = line->line();
                if (point == 0) {
                    l.setP1(l.p1() + delta);
                } else if (point == 1) {
                    l.setP2(l.p2() + delta);
                }
                line->setLine(l);
                //m_scene->update(m_scene->sceneRect());
            }
        }
    }
    else if (m_mode == CanvasMode::DrawPolygon) {
        if (m_current_line) {
            auto l = m_current_line->line();
            l.setP2(cur);
            m_current_line->setLine(l);
        }
    }
    else {
        QGraphicsView::mousePressEvent(event);
    }
    m_prev = cur;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    qDebug("Mouse release");
    QGraphicsView::mousePressEvent(event);
}

void Canvas::setDrawPolygonMode() {
    qDebug("Set draw polygon mode");
    m_mode = CanvasMode::DrawPolygon;
    m_has_prev_fixed_point = false;
}

void Canvas::setMovePointMode() {
    qDebug("Set move point mode");
    m_mode = CanvasMode::MovePoint;
}

void Canvas::setRemovePointMode() {
    qDebug("Set remove point mode");
    m_mode = CanvasMode::RemovePoint;
}

void Canvas::setIdleMode() {
    qDebug("Set idle mode");
    m_mode = CanvasMode::Idle;
}

void Canvas::resizeEvent(QResizeEvent *event) {
    qDebug("Resize %dx%d", event->size().width(), event->size().height());
    updateTransform();
}

void Canvas::setCanvasWidth(QString value) {
    bool ok;
    auto v = value.toDouble(&ok);
    if (ok) {
        qDebug("Canvas width changed %f", v);
        m_canvas_width = v;
        updateTransform();
    }
}

void Canvas::setCanvasHeight(QString value) {
    bool ok;
    auto v = value.toDouble(&ok);
    if (ok) {
        qDebug("Canvas height changed %f", v);
        m_canvas_height = v;
        updateTransform();
    }
}

void Canvas::setCanvasAccurace(QString value) {
    bool ok;
    auto v = value.toDouble(&ok);
    if (ok) {
        qDebug("Canvas accuracy changed %f", v);
        m_round_to = v;
        updateTransform();
    }
}

void Canvas::updateTransform() {
    QSize s = size();
    qDebug("Canvas size %dx%d", s.width(), s.height());
    resetTransform();
    scale(m_canvas_width / (qreal)s.width(), m_canvas_height / (qreal)s.height());
    fitInView(0,0, m_canvas_width, m_canvas_height, Qt::KeepAspectRatioByExpanding);
}

void Canvas::roundPoint(QPointF& p) {
    int v = (int)m_round_to;
    if (v <= 0)
        return;
    int x = (int)p.x();
    int y = (int)p.y();
    x = x - x % v;
    y = y - y % v;
    p.setX((qreal)x);
    p.setY((qreal)y);
}

bool Canvas::validateSchema(QList<QGraphicsLineItem*>* _ordered_list) {
    auto items = m_scene->items();
    QList<QGraphicsLineItem*> lines;
    //  select all lines
    for (auto item : items) {
        QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(item);
        if (!line)
            continue;
        lines.push_back(line);
    }
    if (lines.size() < 4)
        return false;
    //  check if perimeter is closed and sort
    QList<QGraphicsLineItem*> ordered_list;
    QGraphicsLineItem* current_line = nullptr;
    while (!lines.empty()) {
        if (!current_line) {
            qDebug("Select first line");
            current_line = lines.front();
            lines.pop_front();
            ordered_list.push_back(current_line);
        }
        auto end = current_line->line().p2() * current_line->transform();
        bool found = false;
        qDebug("Search for the next segment");
        for (int i = 0; i < lines.size(); ++i) {
            //qDebug("Test line %d", i);
            //qDebug("Check start of the line");
            auto start = lines[i]->line().p1() * lines[i]->transform();
            auto dst = (start - end).manhattanLength();
            qDebug("Distance %f", dst);
            if (dst < 0.01) {
                qDebug("Found next segment %d", i);
                ordered_list.push_back(lines[i]);
                current_line = lines[i];
                lines.removeAt(i);
                found = true;
                break;
            }
            qDebug("Check end of the line");
            start = lines[i]->line().p2() * lines[i]->transform();
            dst = (start - end).manhattanLength();
            qDebug("Distance %f", dst);
            if (dst < 0.01) {
                qDebug("Found next segment %d", i);
                //  swap line ends
                auto l = lines[i]->line();
                l.setPoints(l.p2(), l.p1());
                lines[i]->setLine(l);
                ordered_list.push_back(lines[i]);
                current_line = lines[i];
                lines.removeAt(i);
                found = true;
                break;
            }
        }
        if (!found) {
            if (!lines.empty()) {
                qDebug("Can't find line the follows current one");
                return false;
            }
        }
    }
    qDebug("All lines have been ordered");
    if (_ordered_list) {
        *_ordered_list = ordered_list;
    }
    return true;
}


void Canvas::checkSchema() {
    if (!validateSchema(nullptr))
        QMessageBox::critical(this, "Error", "Contour should be closed");
    else
        QMessageBox::information(this, "Info", "Schema is correct");

}

void Canvas::setCurrentSchema(BuildingSchema* value) {
    m_schema = value;
    m_scene->clear();
    m_cursor = m_scene->addEllipse(-5, -5, 10, 10);
    if (m_schema) {
        auto polygon  = m_schema->polygon()->toPolygonF();
        for (int i = 0, max_i = polygon.size(); i < max_i; ++i) {
            auto p1 = polygon.at(i % max_i);
            auto p2 = polygon.at((i +1) % max_i);
            auto line = m_scene->addLine(QLineF(p1, p2));
            line->setPen(m_contour_pen);
        }
    }
}

void Canvas::deletePointArray(int index) {
    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM points WHERE points.id IN (SELECT point_arrays.point_id FROM point_arrays WHERE point_arrays.id=:id)");
    q.bindValue("id", index);
    if (q.exec()) {
        qDebug("Points of the point array %d where removed", index);
    } else {
        qDebug("Failed to remove points of point array %d", index);
    }
}

void Canvas::saveContour() {
    QList<QGraphicsLineItem*> ordered_list;
    if (!validateSchema(&ordered_list)) {
        QMessageBox::critical(this, "Error", "Can't save invalid contour");
        return;
    }
    removeDoubles(&ordered_list);
    if (m_schema) {
        m_schema->polygon()->remove();
        for (auto line : ordered_list) {
            auto p = new Point();
            p->setPointF(line->line().p1() * line->transform());
            m_schema->polygon()->addPoint(p);
        }
        m_schema->updateWalls();
    }
}

void Canvas::removeDoubles(QList<QGraphicsLineItem*>* list) {
    if (!list) {
        qDebug("Can't remove doubles from empty list");
        return;
    }

    int doubles = 0;
    QList<QGraphicsLineItem*> result;
    for (int i = 0, max_i = list->size(); i < max_i; ++i) {
        bool unique = true;
        for (int j = 0, max_j = result.size(); j < max_j; ++j) {
            QPointF a = list->at(i)->line().p1() * list->at(i)->transform();
            QPointF b = list->at(i)->line().p2() * list->at(i)->transform();
            QPointF c = list->at(j)->line().p1() * list->at(j)->transform();
            QPointF d = list->at(j)->line().p2() * list->at(j)->transform();
            if ((a - c).manhattanLength() < 0.1 && (b - d).manhattanLength() < 0.1) {
                unique = false;
                break;
            } else if ((a - d).manhattanLength() < 0.1 && (b - c).manhattanLength() < 0.1) {
                unique = false;
                break;
            }
        }
        if (unique) {
            result.push_back(list->at(i));
        } else {
            doubles++;
        }
    }
    qDebug("Removed %d doubles", doubles);
    *list = result;
}
