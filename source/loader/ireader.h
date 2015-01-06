#ifndef _H_IREADER
#define _H_IREADER

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN

namespace Core {
	class String;
	class Buffer;
}

namespace IoModule {

	DECLARE_PUNK_GUID(IID_IReader, "EEDF5618-4AD1-471C-B745-E1F6D9FBA451");
	DECLARE_PUNK_GUID(CLSID_ColladaReader, "B40A0E52-BF3F-4907-86FE-B7436A33C6A2");

	class IReader : public Core::IObject {
	public:
		virtual Core::Pointer<Core::IObject> Read(const Core::String& filename) = 0;
		virtual Core::Pointer<Core::IObject> Read(Core::Buffer& buffer) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IREADER