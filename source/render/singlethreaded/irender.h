#ifndef _H_IRENDER
#define _H_IRENDER

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace LowLevelRender {
	
	DECLARE_PUNK_GUID(IID_IRender, "F9EF350A-AAE3-45BE-A5F8-71FE6B3CB2B3");
	DECLARE_PUNK_GUID(CLSID_Render, "043B8B3B-3479-4624-B22F-3A81E24487F2");

	class IRender : public Core::IObject {
	public:		
	};
}
PUNK_ENGINE_END

#endif	//	_H_IRENDER_MODULE