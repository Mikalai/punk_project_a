#ifndef _H_IOBJECT
#define _H_IOBJECT

#include <typeinfo>
#include <config.h>
#include <cstdint>
#include <atomic>
#include <memory>
#include "pointer.h"
#include "guid.h"

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

	using IObjectPtr = Core::Pointer < IObject > ;

	extern PUNK_ENGINE_API IObject* GetRootObject();
	extern PUNK_ENGINE_API void DestroyRootObject();
	extern PUNK_ENGINE_API void DestroyObject(IObject* object);

	template<class I> extern Pointer<I> QueryInterfacePtr(Core::Pointer<IObject> source, const Guid& type);
	template<class This> extern void QueryInterface(This* _this, const Guid& type, void** object, std::initializer_list<Guid> supported);
}
PUNK_ENGINE_END

#endif	//	_H_IOBJECT
