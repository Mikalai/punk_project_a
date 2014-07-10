#ifndef _H_ISERIALIZABLE
#define _H_ISERIALIZABLE

#include <config.h>
#include "iobject.h"

PUNK_ENGINE_BEGIN
namespace Core {

	class Buffer;
	
	DECLARE_PUNK_GUID(IID_ISerializable, "6B7C8DC7-0C0B-45F3-8488-F4BE8B0139A2");

	class ISerializable : public IObject {
	public:
		virtual void Serialize(Core::Buffer& buffer) = 0;
		virtual void Deserialize(Core::Buffer& buffer) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ISERIALIZABLE