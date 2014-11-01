#ifndef _H_IMETA_INTERFACE
#define _H_IMETA_INTERFACE

#include <config.h>
#include <core/iobject.h>
#include <string/buffer.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Core {

	DECLARE_PUNK_GUID(IID_IMetaInterface, "D6C2C4DA-1ACF-417D-AF30-07B4772FBD24");
	class IMetaInterface : public Core::IObject {
	public:
		virtual void Invoke(const Core::String& method, Core::Buffer& args) = 0;
	};

}
PUNK_ENGINE_END
#endif	// _H_IMETA_INTERFACE