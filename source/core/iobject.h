#ifndef _H_IOBJECT
#define _H_IOBJECT

#include <typeinfo>
#include <config.h>
#include <cstdint>
#include <atomic>
#include <memory>
#include "unique_ptr.h"
#include "guid.h"
#include "container.h"

PUNK_ENGINE_BEGIN
namespace Core {
	class String;
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

	template<class T>
	void ReleaseObject(T* o) {
		if (o)
			o->Release();
	}	

    template<class I>
    Pointer<I> QueryInterfacePtr(IObject* source, const Guid& type) {
        I* object = nullptr;
        source->QueryInterface(type, (void**)&object);
        return Core::Pointer<I>{object, Core::DestroyObject};
    }

	template < class This >
	void QueryInterface(This* _this, const Guid& type, void** object, std::initializer_list<Guid> supported)
	{
		if (!object)
			return;
		for (auto i : supported) {
			if (type == i) {
				(*object) = (void*)_this;
				_this->AddRef();
				return;
			}
		}
		*object = nullptr;
	}
}
PUNK_ENGINE_END

#endif	//	_H_IOBJECT
