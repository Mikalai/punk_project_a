#ifndef _H_IACTION
#define _H_IACTION

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IAction, "81D98892-B9A8-4571-B30B-CEC355EE837E");

	class IAction : public Core::IObject {
		
	};
}
PUNK_ENGINE_END

#endif