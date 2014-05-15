#include <algorithm>
#include <sstream>
#include "object.h"
#include "string/module.h"

PUNK_ENGINE_BEGIN
namespace Core {

	Object::Object(IObject* parent)
		: m_container{ this, parent }
	{}

	Object::~Object() {}

	void Object::QueryInterface(std::uint64_t type, void** object) {
		*object = nullptr;
		if (typeid(IObject).hash_code() == type) {
			*object = (void*)this;
			AddRef();
		}
	}

	std::uint32_t Object::AddRef() {
		m_ref_count.fetch_add(1);
		return m_ref_count;
	}

	std::uint32_t Object::Release() {
		if (!m_ref_count.fetch_sub(1)) {
			delete this;
		}
		return m_ref_count;
	}


	void Object::SetOwner(IObject* object) {
		m_container.SetOwner(object);
	}

	IObject* Object::GetOwner() {
		return m_container.GetOwner();
	}

	const IObject* Object::GetOwner() const {
		return m_container.GetOwner();
	}

	const Core::String Object::ToString() const {
		return "Object";
	}

	std::uint64_t Object::GetType() {
		return typeid(Object).hash_code();
	}

	void Object::Add(IObject* object) {
		m_container.Add(object);
	}

	void Object::RemoveChild(IObject* object, bool depth) {
		m_container.RemoveChild(object, depth);
	}

	void Object::RemoveChild(std::uint32_t index) {
		m_container.RemoveChild(index);
	}

	IObject* Object::GetChild(std::uint32_t index) {
		return m_container.GetChild(index);
	}

	const IObject* Object::GetChild(std::uint32_t index) const {
		return m_container.GetChild(index);
	}

	std::uint32_t Object::GetChildrenCount() const {
		return m_container.GetChildrenCount();
	}

	Object* g_root_object{ nullptr };

	extern PUNK_ENGINE_API IObject* GetRootObject() {
		if (!g_root_object)
			g_root_object = new Object(nullptr);
		return g_root_object;
	}

	extern PUNK_ENGINE_API void DestroyRootObject() {
		delete g_root_object;
	}
}
PUNK_ENGINE_END
            