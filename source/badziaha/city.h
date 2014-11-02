#ifndef _H_CITY
#define _H_CITY

#include <memory>
#include "entity.h"

class QGraphicsItem;

class CityTask;
class GlobalField;
struct GlobalFieldCell;

enum class CityBuilding {
	No,
	Sawmill
};

class Unit;

class City : public Entity {
	Q_OBJECT;
public:

	City(GlobalField* field, QObject* parent = nullptr);
	void update() override;

	void buildRoad(GlobalFieldCell* start, GlobalFieldCell* end);
	void addTask(CityTask* value);

signals:
	void clicked(City* item);

private:	

	std::vector<CityTask*> m_tasks;
	std::vector<std::unique_ptr<Unit>> m_workers;
	std::vector<std::unique_ptr<Unit>> m_warriors;

	//	population generation
	float m_worker_train_time_base{ 300 };
	float m_warrior_train_time_base{ 600 };

	//	task building
	bool m_build{ false };
	float m_build_time_left{ 0 };
	CityBuilding m_building{ CityBuilding::No };
	GlobalFieldCell* m_build_cell{ nullptr };

};

#endif	//	_H_CITY