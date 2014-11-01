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
	if (m_field->getPath(start->position, end->position, m_path)) {
		for (auto& cell : m_path) {
			cell->addRoad(this);
		}
	}

	//	model should be created after the road was specified
	m_model = new RoadGraphicsItem{ this, nullptr };
	m_field->addRoad(this);
}

Road::~Road() {
	for (auto& cell : m_path) {
		cell->removeRoad(this);
	}
	m_field->removeRoad(this);
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