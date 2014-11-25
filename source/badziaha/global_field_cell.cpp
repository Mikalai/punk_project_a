#include <QtGui/qpainter.h>
#include "global_field.h"
#include "global_field_cell.h"

float GlobalFieldCell::getBaseMoveDifficulty() const {
	if (!m_roads.empty())
		return 0.1f;
	return surface()->movePenalty();
}

GlobalFieldCell::GlobalFieldCell(GlobalField* field, QGraphicsItem* parent) 
	: FieldCell{ parent }
	, m_field{ field }
{
	//QMatrix m{};
	//m.translate(scenePosm_cell->position.x()*CELL_SIZE, m_cell->position.y()*CELL_SIZE);
	//setTransform(QTransform(m));
	setZValue(0.0f);
}


QRectF GlobalFieldCell::boundingRect() const {
	return QRectF(0, 0, GLOBAL_FIELD_CELL_REAL_SIZE, GLOBAL_FIELD_CELL_REAL_SIZE);
}

void GlobalFieldCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	//auto brush = GetGroundBrush();
	
	auto dx = transform().dx();
	auto dy = transform().dy();
	auto p = pos();
	auto sp = scenePos();
	auto pen = painter->pen();
	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setWidth(0);
	painter->setPen(pen);
	auto brush = painter->brush();
	brush.setTextureImage(field()->surface(sp)->icon());
	QMatrix m;
	auto s = 64 / (float)GLOBAL_FIELD_CELL_REAL_SIZE;
	m.scale(s, s);
	brush.setMatrix(m.inverted());
	painter->setBrush(brush);
	//painter->setBrush(brush);
	painter->drawRect(0, 0, GLOBAL_FIELD_CELL_REAL_SIZE, GLOBAL_FIELD_CELL_REAL_SIZE);
	//painter->drawText(QPointF{ 0, 0 }, QString::number(m_cell->findPath(m_field->getTlsIndex())->full_path_cost));
}


void GlobalFieldCell::update() {

}

bool GlobalFieldCell::isNeighbour(GlobalFieldCell* cell) const {
	if (cell == this)
		return false;

	for (int y = -1; y < 2; ++y) {
		for (int x = -1; x < 2; ++x) {
			if (x == 0 && y == 0)
				continue;

			if (index().x() + x == cell->index().x() && index().y() + y == cell->index().y())
				return true;
		}
	}
	return false;
}

int GlobalFieldCell::magic() const {
	auto i = index();
	return i.x() + i.y() * 1024;
}

QPoint GlobalFieldCell::index() const {
	int x = (int)pos().x() / cellSize();
	int y = (int)pos().y() / cellSize();
	return QPoint{ x, y };
}

GlobalField* GlobalFieldCell::field() const {
	return qobject_cast<GlobalField*>(scene());
}
