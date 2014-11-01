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
	Squad(GlobalField* field, QObject* parent = nullptr);

	float getBaseSpeed(GlobalFieldCell* cell) const;
	void goTo(GlobalFieldCell* cell);
	void standBy(float seconds);

	void update() override;

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
private:
	float m_speed{ 3 };
	Unit* m_leader;
	bool m_move_path{ false };
	std::list<GlobalFieldCell*> m_path;
	std::map<UnitType, Members> m_forces;
	FindPathResult* m_find_path_result{ nullptr };

	//	goto command data
	bool m_goto{ false };
	GlobalFieldCell* m_goto_cell{ nullptr };

	//	stand by command data
	bool m_stand_by{ false };
	float m_seconds_left{ 0 };
};
#endif	//	_H_SQUAD