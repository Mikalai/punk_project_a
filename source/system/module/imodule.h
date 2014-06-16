#ifndef _H_SYSTEM_IMODULE
#define _H_SYSTEM_IMODULE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace System {
	
	DECLARE_PUNK_GUID(IID_IModule, "443D7D63-702E-40B7-8248-44016E829220");

	class IModule : public Core::IObject {
	public:
	};
}

PUNK_ENGINE_END

#endif	//	_H_SYSTEM_IMODULE