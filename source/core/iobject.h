#ifndef _H_IOBJECT
#define _H_IOBJECT

#include <typeinfo>
#include <config.h>
#include <cstdint>
#include <atomic>
#include <memory>
#include "pointer.h"
#include "guid.h"
#include "container.h"

PUNK_ENGINE_BEGIN
namespace Core {
	class Guid;

	DECLARE_PUNK_GUID(IID_IObject, "B07B8739-46DA-41FF-80FB-02243DBC2D19");

	class IObject {
	public:
		virtual void QueryInterface(const Guid& type, void** object) = 0;
		virtual std::uint32_t AddRef() = 0;
		virtual std::uint32_t Release() = 0;		
	};

	extern PUNK_ENGINE_API IObject* GetRootObject();
	extern PUNK_ENGINE_API void DestroyRootObject();
	extern PUNK_ENGINE_API void DestroyObject(IObject* object);
}
PUNK_ENGINE_END

#endif	//	_H_IOBJECT
