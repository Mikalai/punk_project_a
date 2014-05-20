#include <string/string.h>
#include <system/errors/module.h>
#include <system/logger/default_logger.h>
#include "module_manager.h"

#ifdef _WIN32
#include <Windows.h>
#endif

PUNK_ENGINE_BEGIN
namespace System {
	extern PUNK_ENGINE_API void LoadModule(const Core::String& module) {
#ifdef _WIN32
		HMODULE hModule = GetModuleHandle((LPCWSTR)(module + ".dll").Data());
		if (hModule) {
			GetDefaultLogger()->Warning("Module '" + module + "' already loaded");
			return;
		}

		hModule = LoadLibraryW((LPCWSTR)(module + ".dll").Data());
		if (!hModule)
			throw System::Error::SystemException("Can't load module " + module);
		return;
#endif
		throw System::Error::SystemException("Not implemented");
	}

	extern PUNK_ENGINE_API void UnloadModule(const Core::String& module) {
#ifdef _WIN32		
		HMODULE hModule = GetModuleHandle((LPCWSTR)(module + ".dll").Data());
		if (!hModule) {
			GetDefaultLogger()->Warning("Module " + module + " was not loaded");
			return;
		}
		FreeLibrary(hModule);
#endif
		throw System::Error::SystemException("Not implemented");
	}
}
PUNK_ENGINE_END
