#include <chrono>
#include "global_field_cell.h"

float GlobalFieldCell::getBaseMoveDifficulty() const {
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