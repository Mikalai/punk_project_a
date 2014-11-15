#ifndef _H_CHARACTER
#define _H_CHARACTER

#include <array>
#include <memory>
#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include "entity.h"
#include "enum_helper.h"

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
	float powerConsume(Activity value) { return m_consume_power[enum_index(value)]; }
	
	static ActivityClass* instance();
	static void destroy();

private:
	std::array<float, enum_size<Activity>::Value> m_consume_power;
	static std::unique_ptr<ActivityClass> m_instance;
};

class UnitModel;
class GlobalField;
class City;
class Squad;
class Character;
class WeatherStamp;

class BodyPart {
public:
	float windProtection();
	float heatAbsorbingFactor();
};

class Body {
public:
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

	std::vector<BodyPart> parts;
	
	Character* character() const { return m_character; }

private:
	Character* m_character{ nullptr };
	float m_emissivity{ 0.98f };
	float m_metabolism_constant{ 60 };
	float m_fat{ 20 };
	float m_muscle{ 70 };
	float m_temperature{ 36.6f };
	float m_surface{ 1.7 };
	float m_max_evaporation_per_hour{ 1.5 }	//	L / h
};

class Character : public Entity {
	Q_OBJECT;
public:
	Character(GlobalField* field, QObject* parent = nullptr);

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
	Building* building() const;
	std::vector<HeatSource> heatSources() const;

private:
	void setCity(City* value) { m_current_city = value; }
	void setSquad(Squad* value) { m_current_squad = value; }

	friend void joinSquad(Squad* squad, Character* Character);
	friend void leaveSquad(Character* Character);

	friend void enterCity(City* city, Character* Character);
	friend void leaveCity(Character* Character);	

private:
	QString m_name{ "Vitaŭt" };
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
};

#endif	//_H_Character