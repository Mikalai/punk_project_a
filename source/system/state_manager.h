#ifndef _H_PUNK_SYSTEM_STATE
#define _H_PUNK_SYSTEM_STATE

#include <vector>
#include <stack>
#include <core/poolable.h>
#include <system/errors/module.h>
#include "smart_pointers/proxy.h"
#include "errors/module.h"

PUNK_ENGINE_BEGIN
namespace System
{
	template<class T>
    class State : public Core::Poolable<State<T>>
	{
	public:

		T& Get() { return m_core; }
		const T& Get() const { return m_core; }
	private:
		T m_core;
	};

	template<class T>
	class StateManager
	{
	public:
		StateManager()
		{
			m_current_state = new State<T>;
		}

		~StateManager()
		{
			delete m_current_state;
            m_current_state = 0;
			while (!m_states.empty())
			{
				delete m_states.top();
				m_states.pop();
			}
		}

		State<T>* CurrentState() { return m_current_state; }

		void Push()
		{
			m_states.push(m_current_state);
			m_current_state = new State<T>(*m_current_state);
		}

		bool Pop()
		{
			if (m_states.empty())
                throw Error::SystemException(L"Error in state stack");

			delete m_current_state;
			m_current_state = m_states.top();
			m_states.pop();
			return true;
		}

	private:
		State<T>* m_current_state;
		std::stack<State<T>*> m_states;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SYSTEM_STATE
