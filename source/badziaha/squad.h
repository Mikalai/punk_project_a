#ifndef _H_SQUAD
#define _H_SQUAD

#include <QtCore/qobject.h>
#include <QtCore/qdatetime.h>
#include <chrono>
#include <map>
#include <QtWidgets/qgraphicsitem.h>
#include "entity.h"
#include "time_dependent.h"

class Character;
class GlobalFieldCell;
class GlobalField;
struct FindPathResult;
class SquadTask;
class Squad;

class SquadTask : public TimeDependent {
public:
	SquadTask(Squad* squad);

private:
	Squad* m_squad{ nullptr };
};

class ExploreFieldCellTask : public SquadTask {
public:

	ExploreFieldCellTask(Squad* squad, GlobalFieldCell* cell);
	void update() override;

private:
	GlobalFieldCell* m_cell{ nullptr };
	float m_progress{ 0 };	
};

class Squad : public Entity {
	Q_OBJECT;
	Q_PROPERTY(Character* leader MEMBER m_leader);
public:
	Squad(Character* leader, GlobalField* field, QGraphicsItem* parent = nullptr);

	float getBaseSpeed(GlobalFieldCell* cell) const;
	void goTo(GlobalFieldCell* cell);
	void standBy(float seconds);

	void update() override;

	Character* leader() { return m_leader; }

	const std::vector<Character*>& party() const { return m_party; }	

	GlobalField* field();

private:

	struct Members {
		Character* m_Character{ nullptr };
		int m_count{ 0 };
		int m_injured{ 0 };
	};
	
	void updateAi();
	void updateHuman();

	
	void movePath(const std::list<GlobalFieldCell*>& path);
	void terminateAnyActivity();
	bool IsIdle();

	//	membership managment
	void addCharacter(Character* Character);
	void removeCharacter(Character* Character);

	friend void joinSquad(Squad* squad, Character* Character);
	friend void leaveSquad(Character* Character);

private:
	//	members
	Character* m_leader{ nullptr };
	std::vector<Character*> m_party;

	//	parameters
	float m_speed{ 3 };	
	bool m_move_path{ false };
	std::list<GlobalFieldCell*> m_path;
	//std::map<CharacterType, Members> m_forces;
	FindPathResult* m_find_path_result{ nullptr };

	//	goto command data
	bool m_goto{ false };
	GlobalFieldCell* m_goto_cell{ nullptr };

	//	stand by command data
	bool m_stand_by{ false };
	float m_seconds_left{ 0 };

	//	squad tasks
	std::vector<SquadTask*> m_tasks;
};

void joinSquad(Squad* squad, Character* Character);
void leaveSquad(Character* Character);

#endif	//	_H_SQUAD