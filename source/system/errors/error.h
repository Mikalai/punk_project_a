#ifdef _WIN32
#ifndef _H_PUNK_ERROR_WIN32
#define _H_PUNK_ERROR_WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#include <Windows.h>
#include "config.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System {
#ifdef _DEBUG
    extern PUNK_ENGINE_API void CheckOSError(const Core::string& msg);
    extern PUNK_ENGINE_API void CheckOSError(LONG code, const Core::string& msg);
#define CHECK_SYS_ERROR(X) CheckOSError(X);
#define CHECK_SYS_ERROR_CODE(CODE, X) CheckOSError(CODE, X)
#else
#define CHECK_SYS_ERROR(X)
#define CHECK_SYS_ERROR_CODE(CODE, X)
#endif	//	_DEBUG

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_ERROR_WIN32
#endif	//	_WIN32
