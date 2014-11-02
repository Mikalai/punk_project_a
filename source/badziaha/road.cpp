#include <memory>
#include "global_field.h"
#include "global_field_cell.h"
#include "road_graphics_item.h"
#include "road.h"

Road::Road(GlobalField* field, GlobalFieldCell* start, GlobalFieldCell* end, QObject* parent)
	: QObject{ parent }
	, m_field{ field }
	, m_start{ start }
	, m_end{ end }
{
	if (start && end) {
		if (m_field->getPath(start->position, end->position, m_path)) {
			for (auto& cell : m_path) {
				cell->addRoad(this);
			}
		}
		
	}
	m_model = new RoadGraphicsItem{ this, nullptr };
}

Road::~Road() {	
}

bool Road::split(GlobalFieldCell* cell, Road** road_a, Road** road_b) {
	
	if (road_a)
		*road_a = nullptr;
	else
		return false;

	if (road_b)
		*road_b = nullptr;
	else
		return false;

	if (cell == m_path.front() || cell == m_path.back()) {
		*road_a = new Road{ m_field, m_start, m_end, parent() };
		return true;
	}

	auto it = std::find(m_path.begin(), m_path.end(), cell);
	if (it == m_path.end())
		return false;
	
	*road_a = new Road{ m_field, m_start, cell };
	*road_b = new Road{ m_field, cell, m_end };
	return true;
}

void Road::extend(GlobalFieldCell* cell) {
	if (m_start == nullptr && m_end == nullptr) {
		m_start = m_end = cell;		
		m_path.push_back(cell);
		cell->addRoad(this);
	}
	else {
		if (m_start->isNeighbour(cell)) {
			m_path.push_front(cell);
			m_start = cell;
			cell->addRoad(this);
		}
		else if (m_end->isNeighbour(cell)) {
			m_path.push_back(cell);
			m_end = cell;
			cell->addRoad(this);
		}
	}
	static_cast<RoadGraphicsItem*>(m_model)->updateBoundingBox();
}

void Road::removeRoad() {
	for (auto& cell : m_path) {
		cell->removeRoad(this);
	}
}