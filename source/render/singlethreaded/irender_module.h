#ifndef _H_RENDER_MODULE2
#define _H_RENDER_MODULE2

#include <core/iobject.h>
#include <system/module/module.h>

PUNK_ENGINE_BEGIN
namespace LowLevelRender {
	
	DECLARE_PUNK_GUID(IID_IRenderModule, "E4EE3710-7494-4691-B828-087DB94E2266");

	class IRenderModule : public System::IModule {
	public:
	};
}
PUNK_ENGINE_END

#endif	//	_H_RENDER_COMMANDS