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

class Character;
class City;
class Squad;

class City : public Entity {
	Q_OBJECT;
public:

	using RawMaterials = std::array < float, enum_size<RawMaterialType>::Value > ;
	using Characters = std::vector < Character* > ;
	using Tasks = std::vector < CityTask* > ;

	City(GlobalField* field, QObject* parent = nullptr);
	void update() override;

	void buildRoad(GlobalFieldCell* start, GlobalFieldCell* end);
	void addTask(CityTask* value);
	const Tasks& tasks() const { return m_tasks; }

	//	resource management
	void addRawMaterial(RawMaterialType value, float quantity);
	bool reserveRawMaterial(const std::vector<std::pair<RawMaterialType, float>>& value);
	const RawMaterials& rawMaterials() const { return m_raw_materials; }
	float rawMaterial(RawMaterialType value) const { return m_raw_materials[enum_index(value)]; }

	//	Characters management
	const Characters& characters() const { return m_characters; }

	QString name() { return m_name; }
	void setName(QString value) { m_name = value; }
	
	GlobalField* field();
	const GlobalField* field() const;
	
signals:
	void clicked(City* item);

private:
	void addCharacter(Character* Character);
	void removeCharacter(Character* Character);
	friend void enterCity(City* city, Character* Character);
	friend void leaveCity(Character* Character);

private:	

	QString m_name;

	Tasks m_tasks;
	std::vector<std::unique_ptr<Character>> m_workers;
	std::vector<std::unique_ptr<Character>> m_warriors;

	//	population generation
	float m_worker_train_time_base{ 300 };
	float m_warrior_train_time_base{ 600 };

	//	task building
	bool m_build{ false };
	float m_build_time_left{ 0 };
	CityBuilding m_building{ CityBuilding::No };
	GlobalFieldCell* m_build_cell{ nullptr };

	//	resource supply
	RawMaterials m_raw_materials;

	//	general population
	int m_last_updated_character{ 0 };
	std::vector<Character*> m_characters;
};

void enterCity(City* city, Character* Character);
void leaveCity(Character* Character);
void enterCity(City* city, Squad* squad);

#endif	//	_H_CITY