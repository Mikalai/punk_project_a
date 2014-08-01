#ifndef _H_ACTION_MANAGER
#define _H_ACTION_MANAGER

#include <config.h>
#include <stack>

PUNK_ENGINE_BEGIN
namespace Tools {

	class ActionBase {
	public:
		virtual ~ActionBase() {};
		virtual void Do() = 0;
		virtual void Undo() = 0;
		virtual void Redo() = 0;
	};

	class ActionManager {
	public:
				
		static void Do(ActionBase* action) {
			action->Do();
			m_undo_list.push(action);
			ClearRedoList();
		}

		static void Undo() {
			if (m_undo_list.empty())
				return;

			auto action = m_undo_list.top();
			m_undo_list.pop();
			action->Undo();
			m_redo_list.push(action);
		}

		static void Redo() {
			if (m_redo_list.empty())
				return;
			auto action = m_redo_list.top();
			m_redo_list.pop();
			action->Redo();
			m_undo_list.push(action);
		}

		static void ClearRedoList() {
			while (!m_redo_list.empty()) {
				auto action = m_redo_list.top();
				delete action;
				m_redo_list.pop();
			}
		}
		static void ClearUndoList() {
			while (!m_undo_list.empty()) {
				auto action = m_undo_list.top();
				delete action;
				m_undo_list.pop();
			}
		}

		static void Clear() {
			ClearUndoList();
			ClearRedoList();
		}

	private:
		static std::stack<ActionBase*> m_undo_list;
		static std::stack<ActionBase*> m_redo_list;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ACTION_MANAGER