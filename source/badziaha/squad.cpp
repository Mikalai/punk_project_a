#include <QtGui/qpixmap.h>
#include <QtWidgets/qgraphicssceneevent.h>
#include <QtGui/qpainter.h>
#include "global_field.h"
#include "global_field_cell.h"
#include "squad.h"
#include "squad_graphics_item.h"

Squad::Squad(GlobalField* field, QObject* parent)
	: Entity{ field, parent }
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
				goTo(field()->getCell(x % field()->getWidth(), y % field()->getHeight()));
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
			auto cell = m_path.front();
			auto target = cell->position;
			auto current = fullPosition();
			if ((target - current).manhattanLength() <= m_speed * dt) {
				auto top = m_path.front();
				setPosition(top->position.x(), top->position.y(), 0, 0);
				m_path.pop_front();
				if (m_path.empty()) {
					m_move_path = false;
				}
			}
			else {
				auto dir = (target - current) / (target - current).manhattanLength();
				dir = dir * getBaseSpeed(cell) * dt;
				move(dir.x(), dir.y());
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