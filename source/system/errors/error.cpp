#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "String/String.h"
#include "error/module.h"
#include "exceptions.h"

PUNK_ENGINE_BEGIN
namespace System
{
    void CheckOSError(const Core::String& msg)
	{
#ifdef _WIN32
        Core::String error;

		DWORD id = GetLastError();
		if (id != S_OK)
		{
            HLOCAL hLocal = 0;
            if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS,
				0, id, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (PTSTR)&hLocal, 0, 0))
			{
				LPVOID p = LocalLock(hLocal);
                error = msg + L" " + Core::String((wchar_t*)p) + Core::String("(Code: {0}) (MS Windows)").arg((int)id);
				LocalFree(hLocal);
			}
			else
			{
                error = msg + L"Unknown error from GetLastError()";
			}
            throw Error::OSException(error);
		}	
#endif
	}

    void CheckOSError(LONG code, const Core::String& msg)
	{
        Core::String error;
#ifdef _WIN32
		if (code != S_OK)
		{
            HLOCAL hLocal = 0;
            if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS,
				0, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (PTSTR)&hLocal, 0, 0))
			{
				LPVOID p = LocalLock(hLocal);
                error = msg + L" " + Core::String((wchar_t*)p) + Core::String("(Code: 0x{0}) (MS Windows)").arg(int(code));
				LocalFree(hLocal);
			}
			else
			{
                error = msg + L" .Unknown error from GetLastError()";
			}
            throw Error::OSException(error);
		}		
#endif
	}
}
PUNK_ENGINE_END

#endif
