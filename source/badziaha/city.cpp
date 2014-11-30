//#include "city.h"
//#include "city_task.h"
//#include "city_graphics_item.h"
//#include "global_field.h"
//#include "character.h"
//#include "squad.h"
//
//City::City(GlobalField* field, QObject* parent)
//	: Entity{ field, parent }
//	, m_name{ "City" }
//{
//	setModel(new CityGraphicsItem{ this });
//	setPosition(0, 0);
//
//	std::fill(m_raw_materials.begin(), m_raw_materials.end(), 0);
//
//	for (auto& raw : m_raw_materials) {
//		raw += 1000.0f;
//	}
//
//	auto character = new Character{ field, parent };
//	character->setName("Citizen");
//	
//}
//
//void City::update() {
//
//	Entity::update();
//	auto dt = getTimeStep();
//
//	//	task building
//	for (auto& task : m_tasks) {
//		task->update();
//	}
//
//	//	remove complete tasks
//	m_tasks.erase(std::remove_if(m_tasks.begin(), m_tasks.end(), [](CityTask* task) {
//		bool flag = task->isComplete();
//		if (flag)
//			delete task;
//		return flag;
//	}), m_tasks.end());
//
//	//	update Characters, one per update
//	if (m_last_updated_character >= m_characters.size())
//		m_last_updated_character = 0;
//	if (!m_characters.empty()) {
//		m_characters.at(m_last_updated_character)->update();
//		m_last_updated_character++;
//	}
//}
//
//void City::buildRoad(GlobalFieldCell* start, GlobalFieldCell* end) {
//	BuildRoad* task = new BuildRoad{ this };
//	task->selectCell(start);
//	task->selectCell(end);
//
//	addTask(task);
//}
//
//void City::addTask(CityTask* task) {
//	m_tasks.push_back(task);
//	field()->addItem(task->model());
//}
//
//void City::addRawMaterial(RawMaterialType value, float quantity) {
//	m_raw_materials[enum_index(value)] += quantity;
//}
//
//bool City::reserveRawMaterial(const std::vector<std::pair<RawMaterialType, float>>& value) {
//	for (int i = 0; i < value.size(); ++i) {
//		auto& r = value[i];
//		auto& stock = m_raw_materials[enum_index(r.first)];
//		if (stock >= r.second) {
//			stock -= r.second;
//		}
//		else {
//			//	revert reserving
//			for (int j = i - 1; j >= 0; --j) {
//				auto& r = value[j];
//				auto& stock = m_raw_materials[enum_index(r.first)];
//				stock += r.second;
//			}
//			return false;
//		}
//	}
//	return true;
//}
//
//void City::addCharacter(Character* value) {
//	auto it = std::find(m_characters.begin(), m_characters.end(), value);
//	if (it != m_characters.end()) {
//		qDebug("Character has been already added");
//		return;
//	}
//
//	m_characters.push_back(value);
//}
//
//void City::removeCharacter(Character* value) {
//	auto it = std::find(m_characters.begin(), m_characters.end(), value);
//	if (it == m_characters.end()) {
//		qDebug("Can't remove Character, was not added");
//		return;
//	}
//
//	m_characters.erase(it);
//}
//
//void enterCity(City* city, Character* Character) {
//
//	auto old_city = Character->city();
//	if (old_city)
//		old_city->removeCharacter(Character);
//
//	Character->setCity(city);
//
//	if (city)
//		city->addCharacter(Character);
//}
//
//void enterCity(City* city, Squad* squad) {
//	enterCity(city, squad->leader());
//
//	for (auto& member : squad->party()) {
//		enterCity(city, member);
//	}
//
//	removeSquad(squad->field(), squad);
//}
//
//void leaveCity(Character* Character) {
//	auto city = Character->city();
//	if (city) {
//		city->removeCharacter(Character);
//		Character->setCity(nullptr);
//	}
//
//	auto squad = new Squad{ Character, city->field(), city->parent() };
//	squad->setHumanControl(Character->isHumanControl());
//	squad->setPosition(city->position());
//
//	addSquad(city->field(), squad);
//}
//
//GlobalField* City::field() {
//	return dynamic_cast<GlobalField*>(Entity::field());
//}
//
//const GlobalField* City::field() const {
//	return dynamic_cast<const GlobalField*>(Entity::field());
//}