#ifndef _H_ISUPPORT_DEBUGGER_TEMPLATE
#define _H_ISUPPORT_DEBUGGER_TEMPLATE

#include <config.h>
#include "stack_trace.h"
#include "isupport_debug.h"
#include "idebugger.h"

PUNK_ENGINE_BEGIN
namespace System {

	template<class T>
	class ISupportDebugImpl : public ISupportDebug {
	protected:
		ISupportDebugImpl() {
			IDebugger::Instance()->TrackInstance(this);
			Stack stack;
			m_creation_place = stack.GetStackTrace();
		}

		virtual ~ISupportDebugImpl() {
			IDebugger::Instance()->UntrackInstance(this);
		}

		virtual const Core::String GetCreationPlace() override {
			return m_creation_place;
		}
	private:
		Core::String m_creation_place;
	};
}
PUNK_ENGINE_END


#endif	//	_H_ISUPPORT_DEBUGGER_TEMPLATE