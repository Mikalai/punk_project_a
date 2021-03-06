#include <sstream>
#include "assert2.h"
#include <system/dbg/stack_trace.h>

#ifdef WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#endif  //  WIN32

PUNK_ENGINE_BEGIN
namespace System
{

#ifdef _DEBUG

	int CustomAssertFunction(bool exp, const Core::String& description, char* func, int line, char* file)
	{
#ifdef WIN32
		Stack walker;
		if (exp)
			return 0;

		std::wstringstream stream;
		stream << description.Data() << L" at " << Core::String(file).Data() << L"(" << line << L") : " << Core::String(func).Data() << std::endl;	
        auto s = walker.GetStackTrace();
        stream << (wchar_t*)s.Data();
		//
		//	copy information in the clipboard
		//
		if (OpenClipboard(NULL))
		{
			HGLOBAL hMem;
			wchar_t* pMem;

			hMem = GlobalAlloc(GHND|GMEM_DDESHARE, (stream.str().length()+1)*sizeof(wchar_t));

			if (hMem)
			{
				pMem = (wchar_t*)GlobalLock(hMem);
				wcscpy_s(pMem, stream.str().length()+1, stream.str().c_str());

				GlobalUnlock(hMem);
				EmptyClipboard();
				SetClipboardData(CF_TEXT, hMem);
			}
			CloseClipboard();
			stream << L"(Information copied to clipboard)";
		}	

		return MessageBox(0, stream.str().c_str(), L"Assert failed", MB_ICONERROR|MB_ABORTRETRYIGNORE);
#elif defined __linux__
        return 0;
#endif
	}
#endif	//	_DEBUG
}
PUNK_ENGINE_END
