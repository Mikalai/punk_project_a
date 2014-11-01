#include <QtGui/qpainter.h>
#include <QtWidgets/qgraphicssceneevent.h>
#include <QtWidgets/qstyleoption.h>
#include <iostream>
#include <stack>
#include "field_cell.h"
#include "field.h"

FieldCell::FieldCell(int x, int y, Field* field)
	: m_index{ x, y }
	, m_field{ field }
{
	//std::cout << "Field cell created " << x << " " << y << std::endl;
	QGraphicsItem::setAcceptHoverEvents(true);
	//QGraphicsItem::setAcceptTouchEvents(true);

	//QGraphicsItem::setActive(true);
	setFlags(QGraphicsItem::ItemIsFocusable);

	auto m = QMatrix();
	m.translate(x * m_width, y * m_width);
	auto t = QTransform(m);
	setTransform(t);
}

QRectF FieldCell::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(0, 0, m_width, m_width);
}

QColor GetColor(int mines_count) {
	switch (mines_count)
	{
	case 1:
		return QColor(0, 0, 255, 255);
	case 2:
		return QColor(0, 127, 0, 255);
	case 3:
		return QColor(255, 0, 0, 255);
	case 4:
		return QColor(255, 255, 0, 255);
	case 5:
		return QColor(255, 0, 255, 255);
	case 6:
		return QColor(0, 255, 255, 255);
	case 7:
		return QColor(127, 0, 255, 255);
	case 8:
		return QColor(255, 127, 0, 255);
	default:
		return QColor(0, 0, 0, 255);
	}
}

void FieldCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	QBrush brush;
	auto r = QRectF(0, 0, m_width, m_width);
	if (m_opened) {
		if (HasMine()) {
			painter->setBrush(QBrush(QColor(200, 200, 200, 255)));
			painter->drawRect(r);
			QRadialGradient gradient(20, 20, 20);
			gradient.setColorAt(0, QColor::fromRgbF(1, 0, 0, 1));
			gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 1));
			brush = QBrush(gradient);
			painter->setBrush(brush);
			auto r = QRectF(3, 3, m_width-6, m_width-6);
			painter->drawEllipse(r);
		}
		else {
			int count = GetNeighbourMinesCount();
			painter->setBrush(QBrush(QColor(200, 200, 200, 255)));
			painter->drawRect(r);
			if (count) {
				auto font = painter->font();
				font.setPointSize(14);
				painter->setPen(GetColor(count));
				painter->setFont(font);
				painter->drawText(QPoint(0.3f * m_width, 0.8f* m_width), QString::number(count));
			}
		}
	}
	else {
		if (!IsMarked()) {
			if (option->state & QStyle::State_MouseOver) {
				QLinearGradient gradient(0, 0, 40, 40);
				gradient.setColorAt(0, QColor::fromRgbF(1, 0, 0, 1));
				gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 1));
				brush = QBrush(gradient);
				//brush.setStyle(Qt::RadialGradientPattern);
			}
			else {
				QLinearGradient gradient(0, 0, 40, 40);
				gradient.setColorAt(0, QColor::fromRgbF(1, 1, 1, 1));
				gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 1));
				brush = QBrush(gradient);
				//brush.setStyle(Qt::RadialGradientPattern);
			}
		}
		else {
			QLinearGradient gradient(0, 0, 40, 40);
			gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
			gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 1));
			brush = QBrush(gradient);
		}
		painter->setBrush(brush);
		painter->drawRect(r);
	}
}

void FieldCell::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
	m_mouse_in = true;
	QGraphicsItem::hoverEnterEvent(event);
}

void FieldCell::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
	m_mouse_in = false;
	QGraphicsItem::hoverLeaveEvent(event);
}

void FieldCell::mouseMoveEvent(QGraphicsSceneMouseEvent * event) {
	std::cout << "Mouse move: " << m_index.x() << " " << m_index.y() << std::endl;
	QGraphicsItem::mouseMoveEvent(event);
}

void FieldCell::mousePressEvent(QGraphicsSceneMouseEvent * event) {
	std::cout << "mousePressEvent: " << m_index.x() << " " << m_index.y() << std::endl;
	event->accept();
	auto buttons = event->buttons();
	if (event->buttons() == (Qt::LeftButton | Qt::RightButton)) {
		if (IsOpened() && GetMarkedMinesCount() >= GetNeighbourMinesCount()) {
			for (int y = -1; y < 2; ++y) {
				for (int x = -1; x < 2; ++x) {
					auto cell = m_field->GetCell(m_index.x() + x, m_index.y() + y);
					if (!cell)
						continue;
					cell->Open();
				}
			}
		}
	}
}

void FieldCell::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	std::cout << "FieldCell mouseReleaseEvent: " << m_index.x() << " " << m_index.y() << std::endl;

	if (event->button() == Qt::RightButton) {
		if (!IsOpened())
			Mark();
	}
	else if (event->button() == Qt::LeftButton) {
		if (!IsMarked()) {
			Open();
		}
	}
	event->accept();
	//QGraphicsItem::mouseReleaseEvent(event);
}

int FieldCell::GetMarkedMinesCount() const {
	auto result = 0;
	for (int y = -1; y < 2; ++y) {
		for (int x = -1; x < 2; ++x) {
			auto cell = m_field->GetCell(m_index.x() + x, m_index.y() + y);
			if (!cell)
				continue;
			if (cell->IsMarked())
				result++;
		}
	}
	return result;
}

int FieldCell::GetNeighbourMinesCount() const {
	auto result = 0;
	for (int y = -1; y < 2; ++y) {
		for (int x = -1; x < 2; ++x) {
			auto cell = m_field->GetCell(m_index.x() + x, m_index.y() + y);
			if (!cell)
				continue;
			if (cell->HasMine())
				result++;
		}
	}
	return result;
}

void FieldCell::Open() {
	std::stack<FieldCell*> cells;
	cells.push(this);
	while (!cells.empty())
	{
		FieldCell* cell = cells.top();
		cells.pop();

		if (cell->IsOpened())
			continue;

		if (cell->IsMarked()) {
			continue;
		}

		//std::cout << "Open cell: " << m_index.x() << " " << m_index.y() << std::endl;
		cell->m_opened = true;

		if (cell->m_has_mine)
			emit explode(cell);

		emit opened(cell);


		int count = cell->GetNeighbourMinesCount();
		//std::cout << "Neighbour mines: " << count << std::endl;


		if (!count) {
			auto result = 0;
			for (int y = -1; y < 2; ++y) {
				for (int x = -1; x < 2; ++x) {
					auto ncell = m_field->GetCell(cell->m_index.x() + x, cell->m_index.y() + y);
					if (!ncell)
						continue;
					if (ncell->IsOpened())
						continue;
					cells.push(ncell);
				}
			}
		}
	}

	scene()->update();
}

void FieldCell::Mark() {
	m_marked = !m_marked;
	emit marked(m_marked);
	scene()->update();
}

void FieldCell::Save(std::ostream& stream) {
	stream.write((char*)&m_index, sizeof(m_index));
	stream.write((char*)&m_opened, sizeof(m_opened));
	stream.write((char*)&m_marked, sizeof(m_marked));
	stream.write((char*)&m_has_mine, sizeof(m_has_mine));
}

void FieldCell::Load(std::istream& stream) {
	stream.read((char*)&m_index, sizeof(m_index));
	stream.read((char*)&m_opened, sizeof(m_opened));
	stream.read((char*)&m_marked, sizeof(m_marked));
	stream.read((char*)&m_has_mine, sizeof(m_has_mine));

	auto m = QMatrix();
	m.translate(m_index.x() * m_width, m_index.y() * m_width);
	auto t = QTransform(m);
	setTransform(t);
}