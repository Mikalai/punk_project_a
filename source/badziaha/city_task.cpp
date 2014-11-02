#include "city_task.h"
#include "unit_graphics_item.h"
#include "road.h"
#include "city.h"
#include "global_field.h"
#include "global_field_cell.h"

CityTask::CityTask(City* city)
	: m_city{ city }
{}


BuildRoad::BuildRoad(City* city)
	: CityTask{ city }
{
	setStage(Stage::Input);
}

void BuildRoad::update() {
	CityTask::update();
	auto dt = getTimeStep();

	if (stage() == Stage::Input) {

	}
	else if (stage() == Stage::Execution) {
		m_time_to_complete_cell -= dt;
		if (m_time_to_complete_cell <= 0) {

			m_road->extend(m_path.front());
			m_path.pop_front();
			m_time_to_complete_cell = .1;

			if (m_path.empty()) {
				qDebug("Build road task complete");
				setStage(Stage::Complete);
				return;
			}
		}
	}
	else if (stage() == Stage::Complete) {		
	}
}

void BuildRoad::selectCell(GlobalFieldCell* cell) {
	if (!needInput())
		return;

	if (!m_start)
		m_start = cell;
	else if (!m_end)
		m_end = cell;

	if (m_start && m_end) {
		if (city()->field()->getPath(m_start->position, m_end->position, m_path)) {			
			m_road = new Road{ city()->field(), nullptr, nullptr, city()->field() };
			city()->field()->addRoad(m_road);
			setStage(Stage::Execution);
		}
		else {
			m_start = m_end = nullptr;
		}
	}
}

//	BUILD
Build::Build(City* city, Entity* result)
	: CityTask{ city }
	, m_entity{ result }
{}

void Build::update() {
	CityTask::update();
	auto dt = getTimeStep();

	if (stage() == Stage::Input){

	}
	else if (stage() == Stage::Execution){
		m_time_to_complete -= dt;
		if (m_time_to_complete < 0) {
			m_entity->setModel(new UnitGraphicsItem < Entity, ModelType::SawMill > { m_entity.get(), nullptr });
			m_entity.release();
			setStage(Stage::Complete);
		}
	}
	else if (stage() == Stage::Complete) {

	}
}

void Build::selectCell(GlobalFieldCell* cell) {
	if (!needInput())
		return;

	if (!m_position) {
		m_position = cell;
		m_entity->setPosition(m_position->position);
		m_entity->setModel(new UnitGraphicsItem < Entity, ModelType::Construction > { m_entity.get(), nullptr });
		city()->field()->addBuilding(m_entity.get());
		setStage(Stage::Execution);
	}
}