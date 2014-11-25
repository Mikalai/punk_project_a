#ifndef _H_CITY_TASK
#define _H_CITY_TASK

#include <list>
#include <memory>
#include "entity.h"
#include <vector>

class Character;
class QPainter;
class GlobalFieldCell;
class GlobalField;
class City;
class Road;
class Construction;

class CityTask : public Entity {
public:

	enum class Stage {
		Input,
		Execution,
		Complete
	};

	CityTask(City* city);
	
	bool isComplete() const {
		return m_stage == Stage::Complete;
	}

	bool needInput() const {
		return m_stage == Stage::Input;
	}

	City* city() {
		return m_city; 
	}

	virtual void selectCell(GlobalFieldCell* cell) = 0;

protected:
	
	void setStage(Stage value) {
		m_stage = value;
	}

	Stage stage() {
		return m_stage;
	}

private:
	Stage m_stage{ Stage::Input };
	City* m_city{ nullptr };
};

class BuildRoad : public CityTask {
public:
	BuildRoad(City* city);
	void update() override;
	void selectCell(GlobalFieldCell* cell) override;

private:
	GlobalFieldCell* m_start{ nullptr };
	GlobalFieldCell* m_end{ nullptr };
	std::list<GlobalFieldCell*> m_path;
	Road* m_road{ nullptr };
	float m_time_to_complete_cell{ 1 };
};

/*
	Build task is used to organize creation of new structures in the global map.
*/
class Build : public CityTask {
public:
	Build(City* city, Construction* e);

	void update() override;
	void selectCell(GlobalFieldCell* cell) override;

private:
	GlobalFieldCell* m_position{ nullptr };
	std::unique_ptr<Construction> m_entity{ nullptr };
	float m_time_to_complete{ 10 };
};

/*
	Explore is used to retrieve information about cell. Retrieved information is stored in the city center.
*/
class Explore : public CityTask {
public:
	Explore(City* city, GlobalFieldCell* cell, Character* leader, std::vector<Character*> members);

	void update() override;
	void selectCell(GlobalFieldCell* cell) override;

private:
	GlobalFieldCell* m_target{ nullptr };
	Character* m_leader{ nullptr };
	std::vector<Character*> m_members;
};

#endif	//	_H_CITY_TASK