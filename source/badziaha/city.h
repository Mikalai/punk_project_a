#ifndef _H_CITY
#define _H_CITY

#include <memory>
#include <array>
#include "entity.h"
#include "enum_helper.h"
#include "raw_material_type.h"

class QGraphicsItem;

class CityTask;
class GlobalField;
struct GlobalFieldCell;

enum class CityBuilding {
	No,
	Sawmill
};

class Unit;
class City;
class Squad;

class City : public Entity {
	Q_OBJECT;
public:

	City(GlobalField* field, QObject* parent = nullptr);
	void update() override;

	void buildRoad(GlobalFieldCell* start, GlobalFieldCell* end);
	void addTask(CityTask* value);
	void addRawMaterial(RawMaterialType value, float quantity);
	bool reserveRawMaterial(const std::vector<std::pair<RawMaterialType, float>>& value);

	QString name() { return m_name; }
	void setName(QString value) { m_name = value; }

	
signals:
	void clicked(City* item);

private:
	void addUnit(Unit* unit);
	void removeUnit(Unit* unit);
	friend void enterCity(City* city, Unit* unit);
	friend void leaveCity(Unit* unit);

private:	

	QString m_name;

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

	//	resource supply
	std::array<float, enum_size<RawMaterialType>::Value> m_raw_materials;

	//	general population
	int m_last_updated_unit{ 0 };
	std::vector<Unit*> m_units;
};

void enterCity(City* city, Unit* unit);
void leaveCity(Unit* unit);
void enterCity(City* city, Squad* squad);

#endif	//	_H_CITY