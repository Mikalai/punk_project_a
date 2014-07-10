#ifndef _H_IRENDER_MODULE
#define _H_IRENDER_MODULE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace LowLevelRender {
	
	DECLARE_PUNK_GUID(IID_IRenderModule, "F9EF350A-AAE3-45BE-A5F8-71FE6B3CB2B3");
	DECLARE_PUNK_GUID(CLSID_RenderModule, "043B8B3B-3479-4624-B22F-3A81E24487F2");

	class IRenderModule : public Core::IObject {
	public:
	};
}
PUNK_ENGINE_END

#endif	//	_H_IRENDER_MODULE