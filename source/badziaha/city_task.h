#ifndef _H_CITY_TASK
#define _H_CITY_TASK

#include <list>
#include <memory>
#include "entity.h"
#include "time_dependent.h"

struct GlobalFieldCell;
class GlobalField;
class City;
class Road;

class CityTask : public TimeDependent {
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

class Build : public CityTask {
public:
	Build(City* city, Entity* e);

	void update() override;
	void selectCell(GlobalFieldCell* cell) override;

private:
	GlobalFieldCell* m_position{ nullptr };
	std::unique_ptr<Entity> m_entity{ nullptr };
	float m_time_to_complete{ 10 };
};

#endif	//	_H_CITY_TASK