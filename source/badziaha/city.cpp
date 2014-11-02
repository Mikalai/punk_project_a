#include "city.h"
#include "city_task.h"
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