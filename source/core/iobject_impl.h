#ifndef _H_CORE_IOBJECT_IMPL
#define _H_CORE_IOBJECT_IMPL

#include "iobject.h"

PUNK_ENGINE_BEGIN
namespace Core {

	template<class T>
	void ReleaseObject(T* o) {
		if (o)
			o->Release();
	}

	template<class I>
	Pointer<I> QueryInterfacePtr(Core::Pointer<IObject> source, const Guid& type) {
		I* object = nullptr;
		source->QueryInterface(type, (void**)&object);
		auto result = Core::Pointer<I>{object, Core::DestroyObject};
		if (object)
			object->Release();
		return result;
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

#endif	//	_H_CORE_IOBJECT_IMPL