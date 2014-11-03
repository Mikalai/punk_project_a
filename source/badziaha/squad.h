#ifndef _H_SQUAD
#define _H_SQUAD

#include <QtCore/qobject.h>
#include <QtCore/qdatetime.h>
#include <chrono>
#include <map>
#include <QtWidgets/qgraphicsitem.h>
#include "unit_type.h"
#include "entity.h"

class Unit;
class GlobalFieldCell;
class GlobalField;
struct FindPathResult;

class Squad : public Entity {
	Q_OBJECT;
	Q_PROPERTY(Unit* leader MEMBER m_leader);
public:
	Squad(Unit* leader, GlobalField* field, QObject* parent = nullptr);

	float getBaseSpeed(GlobalFieldCell* cell) const;
	void goTo(GlobalFieldCell* cell);
	void standBy(float seconds);

	void update() override;

	Unit* leader() { return m_leader; }

	const std::vector<Unit*>& party() const { return m_party; }	

private:

	struct Members {
		Unit* m_unit{ nullptr };
		int m_count{ 0 };
		int m_injured{ 0 };
	};
	
	void updateAi();
	void updateHuman();

	
	void movePath(const std::list<GlobalFieldCell*>& path);
	void terminateAnyActivity();
	bool IsIdle();

	//	membership managment
	void addUnit(Unit* unit);
	void removeUnit(Unit* unit);

	friend void joinSquad(Squad* squad, Unit* unit);
	friend void leaveSquad(Unit* unit);

private:
	//	members
	Unit* m_leader{ nullptr };
	std::vector<Unit*> m_party;

	//	parameters
	float m_speed{ 3 };	
	bool m_move_path{ false };
	std::list<GlobalFieldCell*> m_path;
	//std::map<UnitType, Members> m_forces;
	FindPathResult* m_find_path_result{ nullptr };

	//	goto command data
	bool m_goto{ false };
	GlobalFieldCell* m_goto_cell{ nullptr };

	//	stand by command data
	bool m_stand_by{ false };
	float m_seconds_left{ 0 };
};

void joinSquad(Squad* squad, Unit* unit);
void leaveSquad(Unit* unit);

#endif	//	_H_SQUAD