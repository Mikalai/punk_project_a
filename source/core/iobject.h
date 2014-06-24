#ifndef _H_IOBJECT
#define _H_IOBJECT

#include <typeinfo>
#include <config.h>
#include <cstdint>
#include <atomic>
#include <memory>
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

	template<class T, class Base = IObject>
	using UniquePtr = std::unique_ptr < T, void(*)(Base*) > ;

#define UNIQUE_PTR(T) std::unique_ptr<T, void(*)(Core::IObject*)>

	using IObjectUniquePtr = UniquePtr < IObject > ;

#define PUNK_OBJECT_DEFAULT_IMPL(T) \
	public:\
	std::uint32_t AddRef() {\
	m_ref_count.fetch_add(1);\
	return m_ref_count;\
	}\
	\
	std::uint32_t Release() {\
		if (!(m_ref_count.fetch_sub(1)-1)) {\
			delete this;\
		}\
		return m_ref_count;\
	}\
	private:\
	std::atomic<std::uint32_t> m_ref_count {1}; 

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
