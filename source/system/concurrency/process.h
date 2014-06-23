#ifndef _H_PUNK_PROCESS
#define _H_PUNK_PROCESS

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif	//	_WIN32

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class String;
}
namespace System {

    class PUNK_ENGINE_API Process {
#ifdef _WIN32
        STARTUPINFOW m_startup_info;
		PROCESS_INFORMATION m_process_info;
#endif	// _WIN32
		bool m_is_launched;
	public:
		Process();
		~Process();

        bool Start(const Core::String& cmd_line);
		void Terminate();
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_PROCESS
