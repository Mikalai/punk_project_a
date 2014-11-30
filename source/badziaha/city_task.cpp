//#include <QtGui/qpainter.h>
//#include <QtGui/qtransform.h>
//#include "city_task.h"
//#include "unit_graphics_item.h"
//#include "road.h"
//#include "city.h"
//#include "resources.h"
//#include "buildings.h"
//#include "global_field.h"
//#include "global_field_cell.h"
//#include "squad.h"
//
//CityTask::CityTask(City* city)
//	: Entity{ city->field(), city }
//	, m_city{ city }
//{}
//
//
//BuildRoad::BuildRoad(City* city)
//	: CityTask{ city }
//{
//	setModel(new CharacterGraphicsItem < BuildRoad, ModelType::Construction > { this, nullptr });
//	setStage(Stage::Input);
//}
//
//void BuildRoad::update() {
//	CityTask::update();
//	auto dt = getTimeStep();
//
//	if (stage() == Stage::Input) {
//
//	}
//	else if (stage() == Stage::Execution) {
//		m_time_to_complete_cell -= dt;
//		if (m_time_to_complete_cell <= 0) {
//
//			while (!m_path.empty()) {
//				if (m_path.front()->getRoads().empty())
//					break;
//				m_path.pop_front();
//			}
//
//			if (m_path.empty()) {
//				qDebug("Build road task complete");
//				setStage(Stage::Complete);
//				return;
//			}
//
//			setPosition(m_path.front()->index());
//			m_road->extend(m_path.front());
//			m_path.pop_front();
//			m_time_to_complete_cell = 1;
//
//		}
//	}
//	else if (stage() == Stage::Complete) {		
//	}
//}
//
//void BuildRoad::selectCell(GlobalFieldCell* cell) {
//	if (!needInput())
//		return;
//
//	if (!m_start)
//		m_start = cell;
//	else if (!m_end)
//		m_end = cell;
//
//	if (m_start && m_end) {
//		if (city()->field()->getPath(m_start->index(), m_end->index(), m_path)) {			
//			m_road = new Road{ city()->field(), nullptr, nullptr, city()->field() };
//			setPosition(m_path.front()->index());
//			addRoad(city()->field(), m_road);
//			m_time_to_complete_cell = 0;
//			setStage(Stage::Execution);
//		}
//		else {
//			m_start = m_end = nullptr;
//		}
//	}
//}
//
////	BUILD
//Build::Build(City* city, Construction* result)
//	: CityTask{ city }
//	, m_entity{ result }
//{
//	setModel(new CharacterGraphicsItem < Build, ModelType::Construction > { this, nullptr });
//}
//
//void Build::update() {
//	CityTask::update();
//	auto dt = getTimeStep();
//
//	if (stage() == Stage::Input){
//
//	}
//	else if (stage() == Stage::Execution){
//		m_time_to_complete -= dt;
//		if (m_time_to_complete < 0) {
//			addBuilding(city()->field(), m_entity.release());
//			setStage(Stage::Complete);
//		}
//	}
//	else if (stage() == Stage::Complete) {
//
//	}
//}
//
//void Build::selectCell(GlobalFieldCell* cell) {
//	if (!needInput())
//		return;
//
//	if (!m_position) {
//		setPosition(cell->index());
//		m_position = cell;
//		m_entity->setPosition(m_position->index());
//		//city()->field()->addBuilding(m_entity.get());
//		setStage(Stage::Execution);
//	}
//}
//
////	EXPLORE
//Explore::Explore(City* city, GlobalFieldCell* cell, Character* leader, std::vector<Character*> members) 
//	: CityTask{ city }
//	, m_target{ cell }
//	, m_leader{ leader }
//	, m_members{ members }
//{}
//
//void Explore::update() {
//	if (stage() == Stage::Input) {
//		Squad* s = new Squad{ m_leader, city()->field(), city()->field() };
//	}
//	else if (stage() == Stage::Execution) {
//
//	}
//	else if (stage() == Stage::Complete) {
//
//	}
//}
//
//void Explore::selectCell(GlobalFieldCell* cell) {
//
//}
