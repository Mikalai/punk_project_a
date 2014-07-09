#include <map>
#include <system/filesystem/module.h>
#include <string/module.h>
#include <core/iobject.h>
#include <system/errors/module.h>
#include <system/logger/module.h>
#include "imodule_manager.h"

#ifdef _WIN32
#include <Windows.h>
#elif defined __linux__
#include <dlfcn.h>
#endif

PUNK_ENGINE_BEGIN
namespace System {	
		
#ifdef __linux__
    std::map<Core::String, void*> g_loaded_module;
#endif

	extern PUNK_ENGINE_API Core::Pointer<IModule> LoadModule(const Core::String& module) {
        GetDefaultLogger()->Info("Loading " + module);
#ifdef _WIN32		
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
#elif defined __linux__
        Folder folder;
        Core::String path = "lib" + module+".so";
        GetDefaultLogger()->Info("Loading from " + path);
        auto buffer = path.ToUtf8();
        auto pp = (const char*)buffer.Data();
        void* hModule = dlopen(pp, RTLD_LAZY);
        char* code = dlerror();
        if (!hModule)
            throw System::Error::SystemException("Can't load module " + module + ". " + code);
        g_loaded_module[module] = hModule;

        IModule* (*GetPunkModule)() = (IModule* (*)())dlsym(hModule, "GetPunkModule");
        code = dlerror();
#endif
        if (!GetPunkModule) {
            GetDefaultLogger()->Info("Module '" + module + "' doesn't have GetPunkModule function.");
            return Core::Pointer < IModule > {nullptr, Core::DestroyObject };
        }
        IModule* punk_module = GetPunkModule();
        if (!punk_module) {
            GetDefaultLogger()->Info("Module '" + module + "' was not retrieved from library");
            return Core::Pointer < IModule > {nullptr, Core::DestroyObject};
        }
        punk_module->AddRef();
        return Core::Pointer < IModule > {punk_module, Core::DestroyObject};
	}

	extern PUNK_ENGINE_API void UnloadModule(const Core::String& module) {
#ifdef _WIN32		
		HMODULE hModule = GetModuleHandle((LPCWSTR)(module + ".dll").Data());
		if (!hModule) {
			GetDefaultLogger()->Warning("Module " + module + " was not loaded");
			return;
		}
		FreeLibrary(hModule);
#elif defined __linux__
        auto it = g_loaded_module.find(module);
        if (it == g_loaded_module.end())
            return;
        dlclose(it->second);
#endif
	}
}
PUNK_ENGINE_END
