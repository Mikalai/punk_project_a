#include <math/vec3.h>
#include <math/vec2.h>
#include <math/line2d.h>
#include <QSqlQuery>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsItem>
#include "floor_design.h"
#include "db.h"

using namespace Punk::Engine;
class FloorDesign;
class WallView;

class StairsView : public QGraphicsItem {
public:
    StairsView(StairsSchema* stairs, FloorDesign* view)
        : m_stairs{stairs}
        , m_view{view}
    {
        auto width = stairs->stairsType()->boundingVolume()->width();
        auto height = stairs->stairsType()->boundingVolume()->height();
        auto depth = stairs->stairsType()->boundingVolume()->depth();
        auto p = Math::point2d{*stairs->position()};
        auto p1 = p + Math::point2d{width * 0.5f, depth * 0.5f};
        auto p2 = p + Math::point2d{- width * 0.5f, depth * 0.5f};
        auto p3 = p + Math::point2d{- width * 0.5f, - depth * 0.5f};
        auto p4 = p + Math::point2d{width * 0.5f, - depth * 0.5f};
        m_geometry.append(p1.ToQPointF());
        m_geometry.append(p2.ToQPointF());
        m_geometry.append(p3.ToQPointF());
        m_geometry.append(p4.ToQPointF());
        m_bbox = m_geometry.boundingRect();
        m_brush = QBrush(QColor("Orange"));
    }

    QRectF boundingRect() const
    {
        return m_bbox;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        auto brush = painter->brush();
        painter->setBrush(m_brush);
        painter->drawPolygon(m_geometry);
        painter->setBrush(brush);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        Math::point2d pos{event->scenePos()};
        Math::point2d local{pos.ToQPointF() * sceneTransform().inverted()};
        qDebug("Door %d clicked", m_stairs->id());

        switch (m_view->currentOperation()) {
        default:
            break;
        }
        event->accept();
    }

private:
    QRectF m_bbox;
    QBrush m_brush;
    QPolygonF m_geometry;
    StairsSchema* m_stairs;
    FloorDesign* m_view;
};

class DoorView : public QGraphicsItem {
public:
    DoorView(DoorSchema* window, FloorDesign* view)
        : m_door{window}
        , m_view{view}
    {
        auto width = window->windowType()->boundingVolume()->width();
        auto height = window->windowType()->boundingVolume()->height();
        auto depth = window->windowType()->boundingVolume()->depth();
        auto a = Math::point2d{*window->wall()->pointA()};
        auto b = Math::point2d{*window->wall()->pointB()};
        auto t = window->relativePosition();
        auto p = a + t * (b - a);
        auto l = Math::Line2D(a, b);
        auto n = l.GetNormal().Normalized();
        auto v = l.GetDirection().Normalized();
        auto p1 = p + v * width * 0.5f + n * depth * 0.5f;
        auto p2 = p - v * width * 0.5f + n * depth * 0.5f;
        auto p3 = p - v * width * 0.5f - n * depth * 0.5f;
        auto p4 = p + v * width * 0.5f - n * depth * 0.5f;
        m_geometry.append(p1.ToQPointF());
        m_geometry.append(p2.ToQPointF());
        m_geometry.append(p3.ToQPointF());
        m_geometry.append(p4.ToQPointF());
        m_bbox = m_geometry.boundingRect();
        m_brush = QBrush(QColor("Gray"));
    }

    QRectF boundingRect() const
    {
        return m_bbox;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        auto brush = painter->brush();
        painter->setBrush(m_brush);
        painter->drawPolygon(m_geometry);
        painter->setBrush(brush);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        Math::point2d pos{event->scenePos()};
        Math::point2d local{pos.ToQPointF() * sceneTransform().inverted()};
        qDebug("Door %d clicked", m_door->id());

        switch (m_view->currentOperation()) {
        case FloorDesignOperation::RemoveDoor:
        {
            m_door->wall()->removeDoor(m_door);
            delete m_door;
            delete this;
            break;
        }
            break;
        default:
            break;
        }
        event->accept();
    }

private:
    QRectF m_bbox;
    QBrush m_brush;
    QPolygonF m_geometry;
    DoorSchema* m_door;
    FloorDesign* m_view;
};

class WindowView : public QGraphicsItem {
public:
    WindowView(WindowSchema* window, FloorDesign* view)
        : m_window{window}
        , m_view{view}
    {
        auto width = window->windowType()->boundingVolume()->width();
        auto height = window->windowType()->boundingVolume()->height();
        auto depth = window->windowType()->boundingVolume()->depth();
        auto a = Math::point2d{*window->wall()->pointA()};
        auto b = Math::point2d{*window->wall()->pointB()};
        auto t = window->relativePosition();
        auto p = a + t * (b - a);
        auto l = Math::Line2D(a, b);
        auto n = l.GetNormal().Normalized();
        auto v = l.GetDirection().Normalized();
        auto p1 = p + v * width * 0.5f + n * depth * 0.5f;
        auto p2 = p - v * width * 0.5f + n * depth * 0.5f;
        auto p3 = p - v * width * 0.5f - n * depth * 0.5f;
        auto p4 = p + v * width * 0.5f - n * depth * 0.5f;
        m_geometry.append(p1.ToQPointF());
        m_geometry.append(p2.ToQPointF());
        m_geometry.append(p3.ToQPointF());
        m_geometry.append(p4.ToQPointF());
        m_bbox = m_geometry.boundingRect();
        m_brush = QBrush(QColor("Blue"));
    }

    QRectF boundingRect() const
    {
        return m_bbox;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        auto brush = painter->brush();
        painter->setBrush(m_brush);
        painter->drawPolygon(m_geometry);
        painter->setBrush(brush);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->buttons() & Qt::LeftButton) {
            Math::point2d pos{event->scenePos()};
            Math::point2d local{pos.ToQPointF() * sceneTransform().inverted()};
            qDebug("Window %d clicked", m_window->id());

            switch (m_view->currentOperation()) {
            case FloorDesignOperation::RemoveWindow:
            {
                m_window->wall()->removeWindow(m_window);
                delete m_window;
                delete this;
                break;
            }
                break;
            default:
                break;
            }
            event->accept();
        }
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        event->accept();
    }

private:
    QRectF m_bbox;
    QBrush m_brush;
    QPolygonF m_geometry;
    WindowSchema* m_window;
    FloorDesign* m_view;
};

class WallView : public QGraphicsItem {
public:
    WallView(WallSchema* wall, FloorDesign* view)
        : m_wall{wall}
        , m_view{view}
    {
        QPointF a = *wall->pointA();
        QPointF b = *wall->pointB();
        m_line.setPoints(a, b);
        auto nn = m_line.normalVector().unitVector();
        auto n = QPointF(nn.dx(), nn.dy());
        QPointF p1 = m_line.p1() - 20.0f * n;
        QPointF p2 = m_line.p2() - n * 20.0f;
        QPointF p3 = m_line.p2() + n * 20.0f;
        QPointF p4 = m_line.p1() + n * 20.0f;
        m_geometry.append(p1);
        m_geometry.append(p2);
        m_geometry.append(p3);
        m_geometry.append(p4);
        m_bbox = m_geometry.boundingRect();
        m_brush = QBrush(QColor("Brown"));

        for (int i = 0, max_i = m_wall->windowsCount(); i < max_i; ++i) {
            WindowView* window = new WindowView(m_wall->windowSchema(i), m_view);
            window->setParentItem(this);
        }

        for (int i = 0, max_i = m_wall->doorsCount(); i < max_i; ++i) {
            DoorView* door = new DoorView(m_wall->doorSchema(i), m_view);
            door->setParentItem(this);
        }
    }

    QRectF boundingRect() const
    {
        return m_bbox;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        auto brush = painter->brush();
        painter->setBrush(m_brush);
        painter->drawPolygon(m_geometry);
        painter->setBrush(brush);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        Math::point2d pos{event->scenePos()};
        Math::point2d local{pos.ToQPointF() * sceneTransform().inverted()};
        if (!m_geometry.containsPoint(local.ToQPointF(), Qt::OddEvenFill))
            return;
        Math::point2d org{m_line.p1()};
        Math::point2d dst{m_line.p2()};
        Math::Line2D l{org, local};
        Math::Line2D w{org, dst};
        qDebug("Wall %d clicked", m_wall->id());
        qDebug("Position %f, %f", pos.X(), pos.Y());
        qDebug("Position %f, %f", local.X(), local.Y());
        auto a = Math::vec2{Math::point2d{m_line.p1()}, Math::point2d{m_line.p2()}};
        a.Normalize();
        auto b = l.GetDirection().Normalized();
        auto cos_alpha = a.Dot(b);
        auto p = Math::point2d{m_line.p1()} + l.GetSegmentLength() * cos_alpha * a;
        auto t = w.Parameter(p);
        qDebug("Projected position %f, %f", p.X(), p.Y());
        qDebug("Parameter %f", t);
        switch (m_view->currentOperation()) {
        case FloorDesignOperation::RemoveInnerWall:
            if (m_wall->isInner())  //  only inner walls can be deleted
                delete this;
            break;
        case FloorDesignOperation::AddWindow:
        {
            WindowSchema* window = new WindowSchema(m_wall);
            window->setRelativePosition(t);
            m_wall->addWindowSchema(window);
            WindowView* view = new WindowView(window, m_view);
            view->setParentItem(this);
        }
            break;
        case FloorDesignOperation::AddDoor:
        {
            DoorSchema* door= new DoorSchema(m_wall);
            door->setRelativePosition(t);
            m_wall->addDoorSchema(door);
            DoorView* view = new DoorView(door, m_view);
            view->setParentItem(this);
        }
        default:
            break;
        }
        event->accept();
    }



private:
    QLineF m_line;
    QBrush m_brush;
    QPolygonF m_geometry;
    QRectF m_bbox;
    WallSchema* m_wall{nullptr};
    FloorDesign* m_view;
};

class FloorView : public QGraphicsItem {
public:
    FloorView(FloorSchema* schema, BuildingSchema* building, FloorDesign* view)
        : m_floor{schema}
        , m_view{view}
        , m_building{building}
    {
        m_brush = QBrush(QColor(200, 200, 200, 255));
        auto p = building->polygon()->toPolygonF();
        p.translate(-building->refPoint()->x(), -building->refPoint()->y());
        m_geometry = p;
        m_bbox = m_geometry.boundingRect();
        for (int i = 0, max_i = m_floor->wallsCount(); i < max_i; ++i) {
            WallView* wall = new WallView(m_floor->wallSchema(i), m_view);
            wall->setParentItem(this);
        }
    }

    QRectF boundingRect() const
    {
        return m_bbox;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        auto brush = painter->brush();
        painter->setBrush(m_brush);
        painter->drawPolygon(m_geometry);
        painter->setBrush(brush);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        Math::point2d pos{event->scenePos()};
        Math::point2d local{pos.ToQPointF() * sceneTransform().inverted()};
        if (!m_geometry.containsPoint(local.ToQPointF(), Qt::OddEvenFill))
            return;
        qDebug("Floor %d clicked", m_floor->id());
        qDebug("Position %f, %f", pos.X(), pos.Y());
        qDebug("Position %f, %f", local.X(), local.Y());
        switch (m_view->currentOperation()) {
        case FloorDesignOperation::AddStairs:
        {
            auto next_floor = m_building->nextFloor(m_floor);
            if (next_floor) {
                StairsSchema* stairs = new StairsSchema(m_building, m_floor, next_floor);

            }
        }
            break;
        default:
            break;
        }
        event->accept();
    }

private:
    BuildingSchema* m_building{nullptr};
    FloorSchema* m_floor{nullptr};
    FloorDesign* m_view;
    QPolygonF m_geometry;
    QRectF m_bbox;
    QBrush m_brush;
};

class BuildingItem : public QGraphicsItem {
public:
    BuildingItem(BuildingSchema* schema, FloorDesign* view)
        : m_schema{schema}
        , m_view{view}
    {
        //  resetTransform();
        moveBy(m_schema->refPoint()->x(), m_schema->refPoint()->y());
        m_bbox = m_schema->polygon()->toPolygonF().boundingRect();
        m_bbox.moveTo(-m_schema->refPoint()->x(), -m_schema->refPoint()->y());
        m_geometry = schema->polygon()->toPolygonF();
        m_geometry.translate(-m_schema->refPoint()->x(), -m_schema->refPoint()->y());

        FloorView* floor = new FloorView(m_schema->floorSchema(0), schema, m_view);
        floor->setParentItem(this);
    }

    QRectF boundingRect() const
    {
        return m_bbox;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        painter->drawPolygon(m_geometry);
    }

private:
    QPolygonF m_geometry;
    QRectF m_bbox;
    BuildingSchema* m_schema{nullptr};
    FloorDesign* m_view;
};

FloorDesign::FloorDesign(QWidget *parent) :
    QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    setMouseTracking(true);
    setScene(m_scene);
}

void FloorDesign::mousePressEvent(QMouseEvent *event) {
    qDebug("Mouse press");
    QPointF p = mapToScene(event->pos());
    roundPoint(p);
    qDebug("x: %f; y: %f", p.x(), p.y());
    if (m_current_operation == FloorDesignOperation::AddInnerWall) {
        if (m_curret_inner_wall) {
            auto line = m_curret_inner_wall->line();
            line.setP2(p);
            m_curret_inner_wall->setLine(line);
            auto ref_point = *m_current_schema->refPoint();
            auto p1 = line.p1() * m_curret_inner_wall->transform() - ref_point;
            auto p2 = line.p2() * m_curret_inner_wall->transform() - ref_point;
            //  todo: should be current floor
            WallSchema* wall = new WallSchema(m_current_schema->floorSchema(0));
            wall->setInner(true);
            wall->pointA()->setPointF(p1);
            wall->pointB()->setPointF(p2);
            m_current_schema->floorSchema(0)->addWall(wall);
            m_scene->clear();
            m_scene->addItem(new BuildingItem(m_current_schema, this));
            m_curret_inner_wall = nullptr;
        } else {
            m_curret_inner_wall = m_scene->addLine(QLineF(p, p));
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void FloorDesign::mouseMoveEvent(QMouseEvent *event) {
    //qDebug("Mouse move");
    QPointF p = mapToScene(event->pos());
    roundPoint(p);
    if (m_current_operation == FloorDesignOperation::AddInnerWall) {
        if (m_curret_inner_wall) {
            auto line = m_curret_inner_wall->line();
            line.setP2(p);
            m_curret_inner_wall->setLine(line);
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}

void FloorDesign::mouseReleaseEvent(QMouseEvent *event) {
    qDebug("Mouse release");
    QGraphicsView::mouseReleaseEvent(event);
}

void FloorDesign::resizeEvent(QResizeEvent *event) {
    qDebug("Resize %dx%d", event->size().width(), event->size().height());
    updateTransform(event->size().width(), event->size().height());
}

void FloorDesign::setCurrentFloor(QString value) {
    qDebug("Change current floor %s", value.toStdString().c_str());
    bool ok;
    int index = value.toInt(&ok);
    if (ok && m_current_schema) {
        m_current_floor = m_current_schema->floorSchema(index);
        //updateFloor();
    }
}

void FloorDesign::setCurrentSchema(BuildingSchema* value) {
    qDebug("Set current schema");
    m_current_schema = value;
    if (m_current_schema && m_current_schema->floorsCount()) {
        m_current_floor = m_current_schema->floorSchema(0);
        m_scene->addItem(new BuildingItem(m_current_schema, this));
        //updateFloor();
    }
}

//void FloorDesign::updateFloor() {
//    qDebug("Update floor");
//    if (!m_current_floor)
//        return;
//    m_scene->clear();
//    m_scene->addItem(new BuildingItem(m_current_schema));
//}

void FloorDesign::createFloor() {
    qDebug("Create floor");
    m_scene->clear();
    if (!m_current_schema)
        return;

    m_scene->addItem(new BuildingItem(m_current_schema, this));
    //m_scene->addEllipse(100, 100, 100, 100);
}

void FloorDesign::setCanvasWidth(QString value) {
    bool ok;
    auto v = value.toDouble(&ok);
    if (ok) {
        qDebug("FloorDesign width changed %f", v);
        m_canvas_width = v;
        updateTransform(size().width(), size().height());
    }
}

void FloorDesign::setCanvasHeight(QString value) {
    bool ok;
    auto v = value.toDouble(&ok);
    if (ok) {
        qDebug("FloorDesign height changed %f", v);
        m_canvas_height = v;
        updateTransform(size().width(), size().height());
    }
}

void FloorDesign::setCanvasAccurace(QString value) {
    bool ok;
    auto v = value.toDouble(&ok);
    if (ok) {
        qDebug("FloorDesign accuracy changed %f", v);
        m_round_to = v;
        updateTransform(size().width(), size().height());
    }
}

void FloorDesign::updateTransform(float width, float height) {
    qDebug("FloorDesign size %dx%d", width, height);
    resetTransform();
    scale(m_canvas_width / (qreal)width, m_canvas_height / (qreal)height);
    fitInView(0,0, m_canvas_width, m_canvas_height, Qt::KeepAspectRatioByExpanding);
}


void FloorDesign::roundPoint(QPointF& p) {
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

void FloorDesign::setAddInnerWallMode() {
    m_current_operation = FloorDesignOperation::AddInnerWall;
    qDebug("Mode: AddInnerWall");
}

void FloorDesign::setRemoveInnerWallMode() {
    m_current_operation = FloorDesignOperation::RemoveInnerWall;
    qDebug("Mode: RemoveInnerWall");
}

void FloorDesign::setAddDoorMode() {
    m_current_operation = FloorDesignOperation::AddDoor;
    qDebug("Mode: AddDoor");
}

void FloorDesign::setRemoveDoorMode() {
    m_current_operation = FloorDesignOperation::RemoveDoor;
    qDebug("Mode: RemoveDoor");
}

void FloorDesign::setAddWindowMode() {
    m_current_operation = FloorDesignOperation::AddWindow;
    qDebug("Mode: AddWindow");
}

void FloorDesign::setRemoveWindowMode() {
    m_current_operation = FloorDesignOperation::RemoveWindow;
    qDebug("Mode: RemoveWindow");
}

void FloorDesign::setAddStairsMode() {
    m_current_operation = FloorDesignOperation::AddStairs;
    qDebug("Mode: AddStairs");
}

void FloorDesign::setRemoveStairsMode() {
    m_current_operation = FloorDesignOperation::RemoveStairs;
    qDebug("Mode: RemoveStairs");
}
