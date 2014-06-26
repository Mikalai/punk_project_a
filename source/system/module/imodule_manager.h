#ifndef _H_IMODULE_MANAGER
#define _H_IMODULE_MANAGER

#include <config.h>
#include <core/iobject.h>
#include "imodule.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System {
		
	extern PUNK_ENGINE_API Core::Pointer<IModule> LoadModule(const Core::String& module);
	extern PUNK_ENGINE_API void UnloadModule(const Core::String& module);
}
PUNK_ENGINE_END

#endif	//	_H_IMODULE_MANAGER