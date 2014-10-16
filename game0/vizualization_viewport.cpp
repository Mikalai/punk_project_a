#include <QMouseEvent>
#include <QWheelEvent>
#include "vizualization_viewport.h"

VizualizationViewport::VizualizationViewport(QWidget *widget)
    : QGraphicsView{widget}
{
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setMouseTracking(true);
}

void VizualizationViewport::mouseMoveEvent(QMouseEvent* event) {
    auto p = mapToScene(event->x(), event->y());
   // qDebug("Point %f, %f", p.x(), p.y());
    if (event->buttons() & Qt::RightButton) {
    QPointF delta = p - m_prev_point;
    QTransform t;
    t.translate(delta.x(), delta.y());
    setTransform(t, true);
    }
    m_prev_point = p;
}

void VizualizationViewport::wheelEvent(QWheelEvent* event) {

}

void VizualizationViewport::mousePressEvent(QMouseEvent* event) {
    auto p = mapToScene(event->x(), event->y());
    m_prev_point = p;
}

void VizualizationViewport::mouseReleaseEvent(QMouseEvent* event) {

}

