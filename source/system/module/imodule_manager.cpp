#include <string/string.h>
#include <core/iobject.h>
#include <system/errors/module.h>
#include <system/logger/default_logger.h>
#include "imodule_manager.h"

#ifdef _WIN32
#include <Windows.h>
#endif

PUNK_ENGINE_BEGIN
namespace System {	
		
	extern PUNK_ENGINE_API Core::UniquePtr<IModule> LoadModule(const Core::String& module) {
#ifdef _WIN32
		GetDefaultLogger()->Info("Loading " + module);
		HMODULE hModule = GetModuleHandle((LPCWSTR)(module + ".dll").Data());
		if (hModule) {
			GetDefaultLogger()->Warning("Module '" + module + "' already loaded");			
		}
		else {
			hModule = LoadLibraryW((LPCWSTR)(module + ".dll").Data());
			if (!hModule)
				throw System::Error::SystemException("Can't load module " + module);
		}
		
		IModule* (*GetPunkModule)() = (IModule* (*)())GetProcAddress(hModule, "GetPunkModule");
		if (!GetPunkModule) {
			GetDefaultLogger()->Info("Module '" + module + "' doesn't have GetPunkModule function");
			return Core::UniquePtr < IModule > {nullptr, Core::DestroyObject };
		}
		IModule* punk_module = GetPunkModule();
		if (!punk_module) {
			GetDefaultLogger()->Info("Module '" + module + "' was not retrieved from library");
			return Core::UniquePtr < IModule > {nullptr, Core::DestroyObject};
		}
		punk_module->AddRef();
		return Core::UniquePtr < IModule > {punk_module, Core::DestroyObject};
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
