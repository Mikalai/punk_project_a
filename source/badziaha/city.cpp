#include "city.h"
#include "city_task.h"
#include "city_graphics_item.h"
#include "global_field.h"
#include "unit.h"
#include "squad.h"

City::City(GlobalField* field, QObject* parent)
	: Entity{ field, parent }
	, m_name{ "City" }
{
	setModel(new CityGraphicsItem{ this });
	setPosition(0, 0);

	for (auto& raw : m_raw_materials) {
		raw += 1000.0f;
	}

	auto unit = new Unit{ field, parent };
	unit->setName("Citizen");
	
}

void City::update() {

	Entity::update();
	auto dt = getTimeStep();

	//	task building
	for (auto& task : m_tasks) {
		task->update();
	}

	//	remove complete tasks
	m_tasks.erase(std::remove_if(m_tasks.begin(), m_tasks.end(), [](CityTask* task) {
		bool flag = task->isComplete();
		if (flag)
			delete task;
		return flag;
	}), m_tasks.end());

	//	update units, one per update
	if (m_last_updated_unit >= m_units.size())
		m_last_updated_unit = 0;
	if (!m_units.empty()) {
		m_units.at(m_last_updated_unit)->update();
		m_last_updated_unit++;
	}
}

void City::buildRoad(GlobalFieldCell* start, GlobalFieldCell* end) {
	BuildRoad* task = new BuildRoad{ this };
	task->selectCell(start);
	task->selectCell(end);
	m_tasks.push_back(task);
}

void City::addTask(CityTask* task) {
	m_tasks.push_back(task);
}

void City::addRawMaterial(RawMaterialType value, float quantity) {
	m_raw_materials[enum_index(value)] += quantity;
}

bool City::reserveRawMaterial(const std::vector<std::pair<RawMaterialType, float>>& value) {
	for (int i = 0; i < value.size(); ++i) {
		auto& r = value[i];
		auto& stock = m_raw_materials[enum_index(r.first)];
		if (stock >= r.second) {
			stock -= r.second;
		}
		else {
			//	revert reserving
			for (int j = i - 1; j >= 0; --j) {
				auto& r = value[j];
				auto& stock = m_raw_materials[enum_index(r.first)];
				stock += r.second;
			}
			return false;
		}
	}
	return true;
}

void City::addUnit(Unit* value) {
	auto it = std::find(m_units.begin(), m_units.end(), value);
	if (it != m_units.end()) {
		qDebug("Unit has been already added");
		return;
	}

	m_units.push_back(value);
}

void City::removeUnit(Unit* value) {
	auto it = std::find(m_units.begin(), m_units.end(), value);
	if (it == m_units.end()) {
		qDebug("Can't remove unit, was not added");
		return;
	}

	m_units.erase(it);
}

void enterCity(City* city, Unit* unit) {

	auto old_city = unit->city();
	if (old_city)
		old_city->removeUnit(unit);

	unit->setCity(city);

	if (city)
		city->addUnit(unit);
}

void enterCity(City* city, Squad* squad) {
	enterCity(city, squad->leader());

	for (auto& member : squad->party()) {
		enterCity(city, member);
	}

	squad->field()->removeSq
}

void leaveCity(Unit* unit) {
	auto city = unit->city();
	if (city) {
		city->removeUnit(unit);
		unit->setCity(nullptr);
	}

	auto squad = new Squad{ unit, city->field(), city->parent() };
	squad->setHumanControl(unit->isHumanControl());
	squad->setPosition(city->position());

	city->field()->addSquad();
}