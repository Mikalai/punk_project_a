#ifndef _H_CHARACTER
#define _H_CHARACTER

#include <array>
#include <memory>
#include <queue>
#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include "entity.h"
#include "enum_helper.h"
#include "weather.h"
#include "body_part_type.h"
#include "item_class_type.h"
#include "fwd_items.h"

enum class Activity {
	Idle,
	Run,
	Sleep,
	Walk,
	Sweem,
	End
};

class ActivityClass {
public:

	ActivityClass();

	float powerConsume(Activity value) { return m_consume_power[enum_index(value)]; }
	
	static ActivityClass* instance();
	static void destroy();

private:
	std::array<float, enum_size<Activity>::Value> m_consume_power;
	static std::unique_ptr<ActivityClass> m_instance;
};

class Body;
class Item;
class UnitModel;
class GlobalField;
class City;
class Squad;
class Character;
struct WeatherStamp;
class Clothes;
class BodyPart;

extern void delete_part(BodyPart* value);
extern void delete_clothes(Clothes* value);
extern void delete_item(Item* value);

class BodyPart {
public:

	BodyPart(BodyPartType type, Body* owner)
		: m_body{ owner }
		, m_part{ type }
	{}

	~BodyPart();

	float windProtection() const;
	float heatAbsorbingFactor() const;

	BodyPartType type() const { return m_part; }

	float relativeWeight() const;

	Clothes* clothes() { return m_clothes.get(); }
	void putClothes(ClothesPtr value);
	ClothesPtr dropClothes() { return std::move(m_clothes); }

private:
	BodyPartType m_part{ BodyPartType::LeftFoot };
	ClothesPtr m_clothes{ make_ptr<Clothes>(nullptr) };
	Body* m_body{ nullptr };
};

class Body {
public:
	Body();
	~Body();

	float windProtection() const;
	float heatAbsorbingFactor() const;
	float temperature() const { return m_temperature; }
	void update(float dt);
	float mass() const;
	float surface() const { return m_surface; }
	float projectedSurface() const { return 0.4f*surface(); }
	float energy() const;

	//	power
	float metabolismConstant() const { return m_metabolism_constant; }
	float metabolismPower() const;
	float radiativePower() const;
	float shortWaveRadiation() const;
	float longWaveRadiation() const;
	float evaporationLost() const;
	float emissivity() const { return m_emissivity; }
	float convectionHeat() const;
	float maxWaterEvaporationPerHour() const { return m_max_evaporation_per_hour; }
	float maxPowerSurplus() const;
	float powerSurplus() const;
	void heatBalance(float dt);
	//	returns amount of liters that should be evaporated to consume power
	float powerToEvaporatedWater(float power);

	std::vector<std::unique_ptr<BodyPart>> parts;
	
	Character* character() const { return m_character; }

	void die();

	float minTemperature() const { return m_min_temperature; }
	float maxTemperature() const { return m_max_temperature; }
	float water() const { return m_water; }
	float minWater() const { return m_min_water; }
	float maxWater() const { return m_max_water; }

	bool isAlive() const { return m_alive; }

	BodyPart* part(BodyPartType type) {
		return parts[enum_index(type)].get();
	}

	///	Returns a body part that wear specified clothes
	BodyPart* wearClothes(const Clothes* item);

private:
	void satisfyThirst();

private:
	Character* m_character{ nullptr };
	bool m_alive{ true };
	float m_min_temperature{ 15.0f };
	float m_max_temperature{ 43.0f };
	float m_emissivity{ 0.98f };
	float m_metabolism_constant{ 60 };
	float m_fat{ 20 };
	float m_muscle{ 70 };
	float m_temperature{ 36.6f };
	float m_surface{ 1.7f };
	float m_max_evaporation_per_hour{ 1.5 }; //	L / h		
	float m_water{ 4000.0f };
	float m_min_water{ 1000.0f };
	float m_max_water{ 5000.0f };
};

class Character : public Entity {
	Q_OBJECT;
public:
	Character(GlobalField* field, QObject* parent = nullptr);
	virtual ~Character();

	int builderLevel() const { return m_builder_level; }
	int warriorLevel() const { return m_warrior_level; }

	City* city() { return m_current_city; };
	
	QString name() const { return m_name; }
	void setName(QString value) { m_name = value; }


	Squad* squad() { return m_current_squad; }

	Body* body() { return &m_body; }

	void update() override;

	Activity activity() const { return m_activity; }

	// field or building
	WeatherStamp* weather() const;
	std::vector<HeatSource> heatSources() const;

	// inventory managment
	bool hasItem(const Item* item);
	bool take(ItemPtr item);
	bool putOn(const Clothes* item);
	bool putOff(const Clothes* item);
	void drop(const Item* item);
	const std::vector<const Item*> selectItems(ItemClassType type);
	const std::vector<const Item*> selectEquippedItems(ItemClassType type);
	ItemPtr popItem(const Item* item);

private:
	void processTasks();
	void setCity(City* value) { m_current_city = value; }
	void setSquad(Squad* value) { m_current_squad = value; }

	friend void joinSquad(Squad* squad, Character* Character);
	friend void leaveSquad(Character* Character);

	friend void enterCity(City* city, Character* Character);
	friend void leaveCity(Character* Character);	

private:
	QString m_name{ "Vitaut" };
	Activity m_activity{ Activity::Idle };
	float m_health{ 10 };
	float m_min_damage{ 1 };
	float m_max_damage{ 2 };
	float m_speed{ 1 };
	bool m_can_shoot_air{ false };
	bool m_can_shoot{ false };
	bool m_can_fly{ false };
	float m_attack_distance{ 1 };
	int m_warrior_level{ 0 };
	int m_builder_level{ 0 };
	City* m_current_city{ nullptr };
	Squad* m_current_squad{ nullptr };
	Body m_body;

	//	task managment
	enum class TaskType {
		Idle,
		Eat,
		Drink
	};

	struct Task {
		TaskType type{ TaskType::Idle };
		float time_to_complete{ -1 };
	};

	std::priority_queue < Task, std::vector<Task>> m_tasks;

	//	inventory
	std::vector<ItemPtr> m_items;


	friend bool operator < (const Character::Task& a, const Character::Task& b);
};

inline bool operator < (const Character::Task& a, const Character::Task& b) {
	return a.type < b.type;
}
#endif	//_H_Character