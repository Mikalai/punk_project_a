#include <iostream>
#include <QtWidgets/qmessagebox.h>
#include <QtCore/QDateTime>
#include <time.h>
#include <QtWidgets/qgraphicssceneevent.h>
#include "field.h"
#include "field_cell.h"

Field::Field(QObject* parent)
	: QGraphicsScene{ parent }
{
	
}

void Field::Create(int width, int height, int mines_count) {
	clear();
	m_cells.clear();

	m_size.setX(width);
	m_size.setY(height);
	m_mines_count = mines_count;
	m_mines_left = mines_count;

	m_closed = width * height;

	m_cells.resize(height);
	for (int y = 0; y < height; ++y) {
		m_cells[y].resize(width);
		for (int x = 0; x < width; ++x) {
			FieldCell* cell = new FieldCell(x, y, this);
			connect(cell, SIGNAL(explode(FieldCell*)), this, SLOT(explosion(FieldCell*)));
			connect(cell, SIGNAL(opened(FieldCell*)), this, SLOT(opened(FieldCell*)));
			connect(cell, SIGNAL(marked(bool)), this, SLOT(marked(bool)));
			addItem(cell);
			m_cells[y][x] = cell;
		}
	}
}

void Field::explosion(FieldCell* cell) {
	std::cout << "Explosion detected" << std::endl;
	m_exploded = true;
	emit explode();
}

void Field::opened(FieldCell* cell) {
	m_closed--;
	if (m_closed == m_mines_count && !m_exploded) {
		emit complete();
	}
}

bool Field::IsComplete() const {
	return m_closed == m_mines_count && !m_exploded;
}
void Field::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) {
	QGraphicsScene::mousePressEvent(mouseEvent);
}

void Field::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) {
	std::cout << "Field::mouseMoveEvent" << std::endl;
	auto item = itemAt(mouseEvent->scenePos(), QTransform());
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void Field::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent) {
	std::cout << "Field mouseReleaseEvent" << std::endl;
	if (!m_started) {
		FieldCell* cell = qgraphicsitem_cast<FieldCell*>(itemAt(mouseEvent->scenePos(), QTransform()));
		if (!cell) {
			std::cout << "Cell was not selected";
			return;
		}

		if (m_size.x() * m_size.y() < m_mines_count + 1) {
			QMessageBox::critical(nullptr, tr("Can't create field"), tr("Field can't be created because mines count is too much"));
			return;
		}

		srand(QDateTime::currentMSecsSinceEpoch());
		//	distribute mines
		int mines = m_mines_count;
		int free = m_size.x() * m_size.y();
		while (free > 0 && mines > 0) {
			int x = rand() % m_size.x();
			int y = rand() % m_size.y();
			if (m_cells[y][x]->HasMine() || m_cells[y][x] == cell) {
				while (true) {
					x = rand() % m_size.x();
					y = rand() % m_size.y();

					if (m_cells[y][x]->HasMine() || m_cells[y][x] == cell) {
						continue;
					}
					break;
				}
			}
				/*for (int yy = 0; yy < m_size.y(); ++yy) {
					for (int xx = 0; xx < m_size.x(); ++xx) {
						int t = (x + xx);
						int _x = t % m_size.x();
						int d = t / 10;
						int _y = (y + yy + d) % m_size.y();
						if (m_cells[_y][_x]->HasMine() || m_cells[_y][_x] == cell) {
							continue;
						}
						x = _x;
						y = _y;
						goto find_empty_cell;
					}
				}*/
			/*	QMessageBox::critical(nullptr, tr("Can't create field"), tr("Error during mines distribution"));
			}*/

			//find_empty_cell:
			//std::cout << "Cell " << x << " " << y << " got mine " << std::endl;
			m_cells[y][x]->SetMine(true);
			mines--;
			free--;
		}

		cell->Open();

		m_started = true;
		emit started();
		emit minesCountChanged(m_mines_left);
		std::cout << "Game started..." << std::endl;
	}
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

FieldCell* Field::GetCell(int x, int y) {
	if (x < 0 || x >= m_size.x())
		return nullptr;
	if (y < 0 || y >= m_size.y())
		return nullptr;

	return m_cells[y][x];
}

void Field::marked(bool value) {
	m_mines_left += value ? -1 : 1;
	emit minesCountChanged(m_mines_left);
}

void Field::Save(std::ostream& stream) {
	stream.write((char*)&m_size, sizeof(m_size));
	stream.write((char*)&m_mines_count, sizeof(m_mines_count));
	stream.write((char*)&m_mines_left, sizeof(m_mines_left));
	stream.write((char*)&m_closed, sizeof(m_closed));
	stream.write((char*)&m_started, sizeof(m_started));
	stream.write((char*)&m_exploded, sizeof(m_exploded));
	for (int y = 0; y < m_size.y(); ++y) {
		for (int x = 0; x < m_size.x(); ++x) {
			m_cells[y][x]->Save(stream);
		}
	}
}

void Field::Load(std::istream& stream) {
	stream.read((char*)&m_size, sizeof(m_size));
	stream.read((char*)&m_mines_count, sizeof(m_mines_count));
	stream.read((char*)&m_mines_left, sizeof(m_mines_left));
	stream.read((char*)&m_closed, sizeof(m_closed));
	stream.read((char*)&m_started, sizeof(m_started));
	stream.read((char*)&m_exploded, sizeof(m_exploded));
	QGraphicsScene::clear();
	m_cells.resize(m_size.y());
	for (int y = 0; y < m_size.y(); ++y) {
		m_cells[y].resize(m_size.x());
		for (int x = 0; x < m_size.x(); ++x) {
			if (m_cells[y][x]) {
				//removeItem(m_cells[y][x]);
				//delete m_cells[y][x];
			}
			m_cells[y][x] = new FieldCell(y, 0, this);
			connect(m_cells[y][x], SIGNAL(explode(FieldCell*)), this, SLOT(explosion(FieldCell*)));
			connect(m_cells[y][x], SIGNAL(opened(FieldCell*)), this, SLOT(opened(FieldCell*)));
			connect(m_cells[y][x], SIGNAL(marked(bool)), this, SLOT(marked(bool)));
			addItem(m_cells[y][x]);
			m_cells[y][x]->Load(stream);
		}
	}

	if (m_started)
		emit started();

	emit minesCountChanged(m_mines_left);

	update();
}