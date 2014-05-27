//#include <algorithm>
//#include <sstream>
#include <config.h>
#include "iobject.h"
///#include "string/module.h"
//
PUNK_ENGINE_BEGIN
namespace Core {
	DEFINE_PUNK_GUID(IID_IObject, "B07B8739-46DA-41FF-80FB-02243DBC2D19");
//
//	Object::Object(IObject* parent) {
//		ICompoundObject* o = nullptr;
//		o->QueryInterface(IID_ICompoundObject, (void**)&o);
//		if (!o)
//			throw Error::CoreException("Only compound object can be a parent");
//		m_container.reset(new Container < IObject, ICompoundObject > { this, o });
//	}
//
//	Object::~Object() {}
//
//	void Object::QueryInterface(const Guid& type, void** object) {
//		*object = nullptr;
//		if (IID_IObject == type) {
//			*object = (void*)this;
//			AddRef();
//		}
//	}
//
//	std::uint32_t Object::AddRef() {
//		m_ref_count.fetch_add(1);
//		return m_ref_count;
//	}
//
//	std::uint32_t Object::Release() {
//		if (!m_ref_count.fetch_sub(1)) {
//			delete this;
//		}
//		return m_ref_count;
//	}
//
//
//	void Object::SetOwner(ICompoundObject* object) {
//		ICompoundObject* o = nullptr;
//		o->QueryInterface(IID_ICompoundObject, (void**)&o);
//		if (!o)
//			throw Error::CoreException("Only compound object can be a parent");
//		m_container->SetOwner(o);
//	}
//
//	ICompoundObject* Object::GetOwner() {
//		return m_container->GetOwner();
//	}
//
//	const ICompoundObject* Object::GetOwner() const {
//		return m_container->GetOwner();
//	}
//
//	const Core::String Object::ToString() const {
//		return "Object";
//	}
//
//	std::uint64_t Object::GetType() {
//		return typeid(Object).hash_code();
//	}
//
//	void Object::AddChild(IObject* object) {
//		m_container->AddChild(object);
//	}
//
//	void Object::RemoveChild(IObject* object, bool depth) {
//		m_container->RemoveChild(object, depth);
//	}
//
//	void Object::RemoveChild(std::uint32_t index) {
//		m_container->RemoveChild(index);
//	}
//
//	IObject* Object::GetChild(std::uint32_t index) {
//		return m_container->GetChild(index);
//	}
//
//	const IObject* Object::GetChild(std::uint32_t index) const {
//		return m_container->GetChild(index);
//	}
//
//	std::uint32_t Object::GetChildrenCount() const {
//		return m_container->GetChildrenCount();
//	}
//
//	Object* g_root_object{ nullptr };
//
//	extern PUNK_ENGINE_API IObject* GetRootObject() {
//		if (!g_root_object)
//			g_root_object = new Object(nullptr);
//		return g_root_object;
//	}
//
//	extern PUNK_ENGINE_API void DestroyRootObject() {
//		delete g_root_object;
//	}
//
	extern PUNK_ENGINE_API void DestroyObject(IObject* object) {
		if (object)
			object->Release();
	}
}
PUNK_ENGINE_END
//            