#ifndef _H_UNIT
#define _H_UNIT

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include "entity.h"

class UnitModel;
class GlobalField;
class City;


class Unit : public Entity {
	Q_OBJECT;
public:
	Unit(GlobalField* field, QObject* parent = nullptr);

	int builderLevel() const { return m_builder_level; }
	int warriorLevel() const { return m_warrior_level; }

	City* city() { return m_current_city; };
	

	QString name() const { return m_name; }
	void setName(QString value) { m_name = value; }

	Squad* squad() { return m_current_squad; }

private:
	void setCity(City* value) { m_current_city = value; }
	void setSquad(Squad* value) { m_current_squad = value; }

	friend void joinSquad(Squad* squad, Unit* unit);
	friend void leaveSquad(Unit* unit);

	friend void enterCity(City* city, Unit* unit);
	friend void leaveCity(Unit* unit);	

private:
	QString m_name{ "Vitaŭt" };
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
};

#endif	//_H_UNIT