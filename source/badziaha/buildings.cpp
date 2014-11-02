#include "buildings.h"
#include "unit_graphics_item.h"

Construction::Construction(GlobalField* field, QObject* parent)
	: Entity{ field, parent }
{}


SawMill::SawMill(GlobalField* field, QObject* parent)
	: Construction{ field, parent }
{
	setModel(new UnitGraphicsItem < SawMill, ModelType::SawMill > { this, nullptr });
}

void SawMill::update() {
	Entity::update();
	auto dt = getTimeStep();
	m_wood += m_wood_per_second * dt;
}