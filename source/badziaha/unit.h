#ifndef _H_UNIT
#define _H_UNIT

#include <QtCore/qobject.h>
#include <QtCore/qpoint.h>
#include "entity.h"

class UnitModel;
class GlobalField;

enum class UnitType {
	Worker,
	Warrior
};

class Unit : public Entity {
	Q_OBJECT;
public:
	Unit(GlobalField* field, QObject* parent = nullptr);

	int builderLevel() const { return m_builder_level; }
	int warriorLevel() const { return m_warrior_level; }

	static Unit* create(GlobalField* field, UnitType type, QObject* parent = nullptr);

private:
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
};

#endif	//_H_UNIT