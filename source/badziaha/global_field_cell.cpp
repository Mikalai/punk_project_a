#include <chrono>
#include "global_field_cell.h"

float GlobalFieldCell::getBaseMoveDifficulty() const {
	if (!m_roads.empty())
		return 0.1f;

	switch (ground)
	{
	case GlobalFieldCellGround::Dirt:
		return 4;
	case GlobalFieldCellGround::Forest:
		return 3;
	case GlobalFieldCellGround::Grass:
		return 1;
	case GlobalFieldCellGround::Rocks:
		return 6;
	case GlobalFieldCellGround::Sand:
		return 5;
	case GlobalFieldCellGround::Water:
		return 10;
	default:
		break;
	}
	return 100;
}

GlobalFieldCell::GlobalFieldCell() {
	last_update = std::chrono::high_resolution_clock::now();
}

void GlobalFieldCell::update() {

}

void GlobalFieldCell::addEntity(Entity* value) {
	auto it = std::find(entities.begin(), entities.end(), value);
	if (it != entities.end())
		return;
	entities.push_back(value);
}

void GlobalFieldCell::removeEntity(Entity* value) {
	auto it = std::find(entities.begin(), entities.end(), value);
	if (it == entities.end())
		return;
	entities.erase(it);
}

bool GlobalFieldCell::isNeighbour(GlobalFieldCell* cell) const {
	if (cell == this)
		return false;

	for (int y = -1; y < 2; ++y) {
		for (int x = -1; x < 2; ++x) {
			if (x == 0 && y == 0)
				continue;

			if (position.x() + x == cell->position.x() && position.y() + y == cell->position.y())
				return true;
		}
	}
	return false;
}