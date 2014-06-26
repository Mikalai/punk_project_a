#ifndef _H_SYSTEM_SIGNAL
#define _H_SYSTEM_SIGNAL

#include <config.h>
#include "thread_mutex.h"

PUNK_ENGINE_BEGIN
namespace System {

	class PUNK_ENGINE_API Signal {
	public:
		Signal();
		~Signal();
		void Wait();
		void Raise();
	private:
		ThreadMutex m_mutex;
	};
}
PUNK_ENGINE_END

#endif	//	_H_SYSTEM_SIGNAL