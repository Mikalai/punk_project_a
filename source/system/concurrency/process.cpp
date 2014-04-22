#include <String/module.h>
#include "process.h"

PUNK_ENGINE_BEGIN
namespace System
{
	Process::Process()
	{

#ifdef _WIN32
		memset(&m_startup_info, 0, sizeof(m_startup_info));
        m_startup_info.cb = sizeof(m_startup_info);
#endif	//	_WIN32

	}

	Process::~Process()
	{
#ifdef _WIN32
		CloseHandle(m_process_info.hThread);
		CloseHandle(m_process_info.hProcess);		
#endif	//	_WIN32
	}

    bool Process::Start(const Core::String& cmd_line)
	{
#ifdef _MSC_VER
		wchar_t buf[MAX_PATH];
		wcsncpy_s(buf, MAX_PATH, (const wchar_t*)cmd_line.ToWchar().Data(), MAX_PATH);
		return m_is_launched = (TRUE == CreateProcessW(NULL, buf, NULL, NULL, TRUE, 0, 0, 0, &m_startup_info, &m_process_info));
#elif defined _WIN32
        wchar_t buf[MAX_PATH];
        wcsncpy(buf, (const wchar_t*)cmd_line.ToWchar().Data(), MAX_PATH);
        return m_is_launched = (TRUE == CreateProcessW(NULL, buf, NULL, NULL, TRUE, 0, 0, 0, &m_startup_info, &m_process_info));
#elif defined __gnu_linux__
        return false;
#endif
	}

	void Process::Terminate()
	{
		if (m_is_launched)
		{
#ifdef _WIN32
			TerminateProcess(m_process_info.hProcess, 0);
			WaitForSingleObject(m_process_info.hProcess, INFINITE);
#endif	//	_WIN32
		}
	}
}
PUNK_ENGINE_END
