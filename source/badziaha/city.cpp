#include "city.h"
#include "city_graphics_item.h"
#include "global_field.h"
#include "unit.h"

City::City(GlobalField* field, QObject* parent)
	: Entity{ field, parent }
{
	setModel(new CityGraphicsItem{ this });
	setPosition(0, 0);
	
}

void City::update() {

	Entity::update();
	auto dt = getTimeStep();

	//	task building
	if (m_build) {
		m_build_time_left -= dt;
		if (dt < 0) {

		}
	}
}