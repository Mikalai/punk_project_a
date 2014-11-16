#include <QtGui/qpixmap.h>
#include <QtWidgets/qgraphicssceneevent.h>
#include <QtGui/qpainter.h>
#include "global_field.h"
#include "global_field_cell.h"
#include "squad.h"
#include "squad_graphics_item.h"
#include "Character.h"

Squad::Squad(Character* leader, GlobalField* field, QObject* parent)
	: Entity{ field, parent }
	, m_leader{ leader }
{
	setPosition(0, 0);
	setModel(new SquadGraphicsItem{ this });
}

void Squad::updateAi() {
	if (IsIdle()) {
		int action = rand() % 2;
		if (action == 0) {
			standBy(rand() % 60);
		}
		else if (action == 1) {
			if (!m_move_path && m_find_path_result == nullptr) {
				auto dx = -5 + rand() % 10;
				auto dy = -5 + rand() % 10;
				auto x = std::max(0, position().x() + dx);
				auto y = std::max(0, position().y() + dy);
				goTo(field()->cell(x % field()->width(), y % field()->height()));
			}
		}
	}
}

void Squad::updateHuman() {

}

void Squad::update() {
	Entity::update();
	auto dt = getTimeStep();

	//	Tasks execution
	if (m_goto) {
		//qDebug("GOTO");

		//	if goto cell is not set, than we do not goto
		if (!m_goto_cell) {
			m_goto = false;
			//qDebug("GOTO empty cell. Cancel GOTO");
			return;
		}

		//	if we are searching for new path - cancel it
		if (m_find_path_result) {
			//qDebug("GOTO search path. Cancle search path");
			field()->cancelGetPath(m_find_path_result);
			m_find_path_result = nullptr;
			return;
		}

		//	if we already move along the path - terminate it
		if (m_move_path) {
			//qDebug("GOTO move along the path. Cancel movement");
			m_path.clear();
			m_move_path = false;
			return;
		}

		//qDebug("GOTO calculate new path");
		m_find_path_result = field()->beginGetPath(position(), m_goto_cell->position);
		m_goto = false;
		return;
	}

	//	process stand by command
	if (m_stand_by) {
		m_seconds_left -= dt;
		if (m_seconds_left < 0) {
			m_seconds_left = 0;
			m_stand_by = false;
		}
	}

	//	got new path
	if (m_find_path_result && m_find_path_result->has_result) {
	//	qDebug("New path calculated. Follow it");
		if (m_find_path_result->has_path) {
			movePath(m_find_path_result->path);
		}
		else {
			m_move_path = false;
		}
		field()->endGetPath(m_find_path_result);
		m_find_path_result = nullptr;
	}

	//	AI execution
	if (isHumanControl()) {
		updateHuman();
	}
	else {
		updateAi();
	}

	//	actual execution of tasks
	if (m_move_path) {
		if (m_path.empty()) {
			m_move_path = false;
		}
		else {			
			auto time = dt;
			while (time > 0 && m_move_path) {
				auto cell = m_path.front();
				auto target = cell->position;
				auto current = fullPosition();
				auto t = (target - current).manhattanLength() / getBaseSpeed(cell);
				if (t < time) {
					auto top = m_path.front();
					setPosition(top->position.x(), top->position.y(), 0, 0);
					m_path.pop_front();
					if (m_path.empty()) {
						m_move_path = false;
					}
					time -= t;
				}
				else {
					auto dir = (target - current) / (target - current).manhattanLength();
					dir = dir * getBaseSpeed(cell) * time;
					move(dir.x(), dir.y());
					time = 0;
				}
			}
		}
	}
}

void Squad::terminateAnyActivity() {
	m_goto = false;
	m_stand_by = false;
	m_move_path = false;
}

bool Squad::IsIdle() {
	return !(m_goto || m_stand_by || m_move_path || m_find_path_result);
}

void Squad::goTo(GlobalFieldCell* cell) {
	if (!cell) {
		return;
	}

	terminateAnyActivity();

	if (!isHumanControl()) {
		m_goto = true;
		m_goto_cell = cell;
	}
	else {
		std::list<GlobalFieldCell*> path;
		field()->getPath(position(), cell->position, path);
		movePath(path);
	}
}

void Squad::movePath(const std::list<GlobalFieldCell*>& path) {
	terminateAnyActivity();
	m_move_path = true;
	m_path = path;
}

float Squad::getBaseSpeed(GlobalFieldCell* cell) const {
	auto move_factor = cell->getBaseMoveDifficulty();
	return m_speed / move_factor;
}

void Squad::standBy(float seconds) {
	terminateAnyActivity();
	m_stand_by = true;
	m_seconds_left = seconds;
}

void Squad::addCharacter(Character* Character) {
	auto it = std::find(m_party.begin(), m_party.end(), Character);
	if (it != m_party.end()) {
		qDebug("Can't add Character to squad. Already in the squad");
		return;
	}
	m_party.push_back(Character);
}

void Squad::removeCharacter(Character* Character) {
	auto it = std::find(m_party.begin(), m_party.end(), Character);
	if (it == m_party.end()) {
		qDebug("can't remove Character from squad. Not added");
		return;
	}
	m_party.erase(it);
}

void joinSquad(Squad* squad, Character* Character) {
	auto old_squad = Character->squad();
	if (old_squad)
		old_squad->removeCharacter(Character);

	Character->setSquad(squad);

	if (squad) {
		squad->addCharacter(Character);
	}
}

void leaveSquad(Character* Character) {
	auto squad = Character->squad();

	if (!squad) {
		qDebug("Can't leave squad. Not in squad");
		return;
	}
		squad->removeCharacter(Character);
		Character->setSquad{ nullptr };

	auto own_squad = new Squad{ Character, squad->field(), Character->parent() };
	own_squad->setHumanControl(Character->isHumanControl());
	own_squad->setPosition(squad->position());

	addSquad(squad->field(), own_squad);
}

//	SQUAD TASK
SquadTask::SquadTask(Squad* squad)
	: m_squad{ squad }
{}


//	EXPLORE FIELD CELL TASK
ExploreFieldCellTask::ExploreFieldCellTask(Squad* squad, GlobalFieldCell* cell)
	: SquadTask{ squad }
	, m_cell{ cell }
{}

void ExploreFieldCellTask::update() {
	if (m_progress > 100.0f)
		return;

	TimeDependent::update();
	auto dt = getTimeStep();

	m_progress += dt;

	if (m_progress > 100.0f) {
		//	here we can randomly select what resources, building and etc can be revieled after
		//	exploring the cell. Result can depend on the squad skill.
	}	
}

GlobalField* Squad::field() {
	return dynamic_cast<GlobalField*>(Entity::field());
}