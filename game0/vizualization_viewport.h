#ifndef VIZUALIZATION_VIEWPORT_H
#define VIZUALIZATION_VIEWPORT_H

#include <QTransform>
#include <QGraphicsView>

class QWidget;

class VizualizationViewport : public QGraphicsView {
public:

    VizualizationViewport(QWidget* widget);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:
    QGraphicsItem* m_root;
    QPointF m_prev_point;
};

#endif // VIZUALIZATION_VIEWPORT_H
