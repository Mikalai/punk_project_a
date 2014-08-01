#include "action_manager.h"

PUNK_ENGINE_BEGIN
namespace Tools {
	std::stack<ActionBase*> ActionManager::m_undo_list;
	std::stack<ActionBase*> ActionManager::m_redo_list;
}
PUNK_ENGINE_END
