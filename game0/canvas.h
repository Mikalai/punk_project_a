#ifndef CANVAS_H
#define CANVAS_H

#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include "building_schema.h"

enum class CanvasMode {
    Idle,
    DrawPolygon,
    MovePoint,
    RemovePoint
};

enum class SelectionMode {
    No,
    Vertex,
    Edge
};

enum class AllowedMoveDirection {
    Left = 1,
    Right = 2,
    Top = 4,
    Bottom = 8,
    Horizontal = Left | Right,
    Vertical = Top | Bottom,
    Any = Horizontal | Vertical
};

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Canvas(QWidget* parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:

public slots:
    void setDrawPolygonMode();
    void setMovePointMode();
    void setRemovePointMode();
    void setIdleMode();
    void setCanvasWidth(QString value);
    void setCanvasHeight(QString value);
    void setCanvasAccurace(QString value);
    void checkSchema();
    void setCurrentSchema(BuildingSchema* value);
    void saveContour();
private:
    void updateTransform();
    void roundPoint(QPointF& p);
    bool validateSchema(QList<QGraphicsLineItem*>* ordered_list);
    void deletePointArray(int index);
    void removeDoubles(QList<QGraphicsLineItem*>* list);

private:
    QGraphicsScene* m_scene;
    bool m_has_prev_fixed_point{false};
    QPointF m_prev_fixed_point;
    QPointF m_prev;
    CanvasMode m_mode {CanvasMode::Idle};
    QList<QGraphicsLineItem*> m_current_lines;
    QList<int> m_line_index;
    AllowedMoveDirection m_move_direction {AllowedMoveDirection::Any};
    SelectionMode m_selection_mode{SelectionMode::No};
    QGraphicsEllipseItem* m_cursor{nullptr};
    QGraphicsLineItem* m_current_line{nullptr};
    qreal m_canvas_width{5000};
    qreal m_canvas_height{5000};
    qreal m_round_to{100};
    //int m_schema_polygon{-1};

    BuildingSchema* m_schema;
    QBrush m_contour_brush;
    QPen m_contour_pen;
};

#endif // CANVAS_H
