#ifndef _H_IMODULE_MANAGER
#define _H_IMODULE_MANAGER

#include <config.h>
#include <core/iobject.h>
#include "imodule.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System {
		
	extern PUNK_ENGINE_API std::uint32_t GetLoadedPunkModulesCount();
	extern PUNK_ENGINE_API IModule* GetLoadedPunkModule(std::uint32_t index);
	extern PUNK_ENGINE_API IModule* LoadPunkModule(const Core::String& module);
	extern PUNK_ENGINE_API void UnloadPunkModule(const Core::String& module);
	extern PUNK_ENGINE_API void UnloadAllPunkModule();
}
PUNK_ENGINE_END

#endif	//	_H_IMODULE_MANAGER