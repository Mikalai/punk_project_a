#ifndef FLOOR_DESIGN_H
#define FLOOR_DESIGN_H

#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include "building_schema.h"
#include "floor_schema.h"

enum class FloorDesignOperation {
    Idle,
    AddInnerWall,
    RemoveInnerWall,
    AddDoor,
    RemoveDoor,
    AddWindow,
    RemoveWindow,
    AddStairs,
    RemoveStairs
};

class FloorDesign : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FloorDesign(QWidget* parent = 0);
    FloorDesignOperation currentOperation() {
        return m_current_operation;
    }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);

signals:

public slots:
    void setCurrentFloor(QString value);
    void setCurrentSchema(BuildingSchema* value);
    void createFloor();
    void setCanvasWidth(QString value);
    void setCanvasHeight(QString value);
    void setCanvasAccurace(QString value);
    void setAddInnerWallMode();
    void setRemoveInnerWallMode();
    void setAddDoorMode();
    void setRemoveDoorMode();
    void setAddWindowMode();
    void setRemoveWindowMode();
    void setAddStairsMode();
    void setRemoveStairsMode();

private:
    //void updateFloor();
    void updateTransform(float width, float height);
    void roundPoint(QPointF& p);

private:
    BuildingSchema* m_current_schema{nullptr};
    FloorSchema* m_current_floor{nullptr};
    QGraphicsScene* m_scene{nullptr};
    qreal m_canvas_width{5000};
    qreal m_canvas_height{5000};
    qreal m_round_to{100};
    FloorDesignOperation m_current_operation{FloorDesignOperation::Idle};
    QGraphicsLineItem* m_curret_inner_wall{nullptr};
};


#endif // FLOOR_DESIGN_H
