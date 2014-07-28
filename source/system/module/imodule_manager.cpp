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

	std::map<Core::String, IModule*> g_loded_punk_modules;

	extern PUNK_ENGINE_API std::uint32_t GetLoadedPunkModulesCount() {
		return (std::uint32_t)g_loded_punk_modules.size();
	}

	extern PUNK_ENGINE_API IModule* GetLoadedPunkModule(std::uint32_t index) {
		for (auto m : g_loded_punk_modules) {
			if (index == 0)
				return m.second;
			--index;
		}
		return nullptr;
	}

	extern PUNK_ENGINE_API void UnloadAllPunkModule() {
		while (!g_loded_punk_modules.empty()) {
			UnloadPunkModule(g_loded_punk_modules.begin()->first);
		}
	}

	extern PUNK_ENGINE_API IModule* LoadPunkModule(const Core::String& module) {		
		GetDefaultLogger()->Info("Loading " + module);
#ifdef _WIN32		
		HMODULE hModule = GetModuleHandle((LPCWSTR)(module + ".dll").Data());
		if (!hModule) 
			hModule = GetModuleHandle((LPCWSTR)module.Data());
		if (hModule) {
			GetDefaultLogger()->Warning("Module '" + module + "' already loaded");
		}
		else {
			hModule = LoadLibraryW((LPCWSTR)(module + ".dll").Data());
			if (!hModule)
				hModule = LoadLibraryW((LPCWSTR)module.Data());
			if (!hModule)
				throw System::Error::SystemException("Can't load module " + module);
		}

		wchar_t buffer[2048];
		GetModuleFileName(hModule, buffer, 2048);
		Core::String fullpath(buffer);

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
			return nullptr;
		}
		IModule* punk_module = GetPunkModule();
		if (!punk_module) {
			GetDefaultLogger()->Info("Module '" + module + "' was not retrieved from library");
			return nullptr;
		}
		punk_module->SetFullpath(fullpath);
		g_loded_punk_modules[punk_module->GetName()] = punk_module;
		return punk_module;
	}

	extern PUNK_ENGINE_API void UnloadPunkModule(const Core::String& module) {
#ifdef _WIN32		
		auto it = g_loded_punk_modules.find(module);
		if (it != g_loded_punk_modules.end()) {
			it->second->Release();
			g_loded_punk_modules.erase(it);
		}

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
