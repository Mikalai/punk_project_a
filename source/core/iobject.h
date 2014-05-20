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

	DEFINE_PUNK_GUID(IID_IObject, "B07B8739-46DA-41FF-80FB-02243DBC2D19");

	class IObject {
	public:
		virtual void QueryInterface(const Guid& type, void** object) = 0;
		virtual std::uint32_t AddRef() = 0;
		virtual std::uint32_t Release() = 0;
		virtual void SetOwner(IObject* object) = 0;
		virtual IObject* GetOwner() = 0;
		virtual const IObject* GetOwner() const = 0;
		virtual const Core::String ToString() const = 0;
		virtual std::uint64_t GetType() = 0;
		virtual void AddChild(IObject* object) = 0;
		virtual void RemoveChild(IObject* object, bool depth = false) = 0;
		virtual void RemoveChild(std::uint32_t index) = 0;
		virtual IObject* GetChild(std::uint32_t index) = 0;
		virtual const IObject* GetChild(std::uint32_t index) const = 0;
		virtual std::uint32_t GetChildrenCount() const = 0;
	};

	extern PUNK_ENGINE_API IObject* GetRootObject();
	extern PUNK_ENGINE_API void DestroyRootObject();
	extern PUNK_ENGINE_API void DestroyObject(IObject* object);

	template<class T>
	using UniquePtr = std::unique_ptr < T, void(*)(IObject*) > ;

	using IObjectUniquePtr = UniquePtr < IObject > ;

#define PUNK_OBJECT_DEFAULT_IMPL(T) \
	public:\
	void SetOwner(IObject* object) {\
	m_container.SetOwner(object);\
		}\
	\
	std::uint32_t Object::AddRef() {\
	m_ref_count.fetch_add(1);\
	return m_ref_count;\
	}\
	\
	std::uint32_t Object::Release() {\
		if (!m_ref_count.fetch_sub(1)) {\
			delete this;\
		}\
		return m_ref_count;\
	}\
	\
	void Object::QueryInterface(const Guid& type, void** object) {\
	*object = nullptr;\
	if (typeid(IObject).hash_code() == type) {\
		*object = (void*)this;\
		AddRef();\
	}\
	}\
	IObject* GetOwner() {\
		return m_container.GetOwner();\
		}\
	\
	const IObject* GetOwner() const {\
		return m_container.GetOwner();\
		}\
	\
	const Core::String ToString() const {\
		return #T;\
		}\
	\
	std::uint64_t GetType() {\
		return typeid(T).hash_code();\
		}\
	\
	void AddChild(IObject* object) {\
		m_container.AddChild(object);\
		}\
	\
	void RemoveChild(IObject* object, bool depth) {\
		m_container.RemoveChild(object, depth);\
		}\
	\
	void RemoveChild(std::uint32_t index) {\
		m_container.RemoveChild(index);\
		}\
	\
	IObject* GetChild(std::uint32_t index) {\
		return m_container.GetChild(index);\
		}\
	\
	const IObject* GetChild(std::uint32_t index) const {\
		return m_container.GetChild(index);\
		}\
	\
	std::uint32_t GetChildrenCount() const {\
		return m_container.GetChildrenCount();\
		}\
	private:\
	std::atomic<std::uint32_t> m_ref_count; \
	Core::Container<IObject> m_container{this, Core::GetRootObject()};

#define PUNK_OBJECT_DEFAULT_IMPL2(T) \
	public:\
	void SetOwner(IObject* object) {\
	m_container.SetOwner(object);\
			}\
	\
	std::uint32_t AddRef() {\
	m_ref_count.fetch_add(1);\
	return m_ref_count;\
		}\
	\
	std::uint32_t Release() {\
		if (!m_ref_count.fetch_sub(1)) {\
			delete this;\
				}\
		return m_ref_count;\
		}\
	\
	IObject* GetOwner() {\
		return m_container.GetOwner();\
			}\
	\
	const IObject* GetOwner() const {\
		return m_container.GetOwner();\
			}\
	\
	std::uint64_t GetType() {\
		return typeid(T).hash_code();\
			}\
	\
	void AddChild(IObject* object) {\
		m_container.AddChild(object);\
			}\
	\
	void RemoveChild(IObject* object, bool depth) {\
		m_container.RemoveChild(object, depth);\
			}\
	\
	void RemoveChild(std::uint32_t index) {\
		m_container.RemoveChild(index);\
			}\
	\
	IObject* GetChild(std::uint32_t index) {\
		return m_container.GetChild(index);\
			}\
	\
	const IObject* GetChild(std::uint32_t index) const {\
		return m_container.GetChild(index);\
			}\
	\
	std::uint32_t GetChildrenCount() const {\
		return m_container.GetChildrenCount();\
			}\
	private:\
	std::atomic<std::uint32_t> m_ref_count; \
	Core::Container<IObject> m_container{this, Core::GetRootObject()};

#define PUNK_OBJECT_DEFAULT_IMPL3(T) \
	public:\
	void SetOwner(IObject* object) {\
	m_container.SetOwner(object);\
				}\
	\
	std::uint32_t AddRef() {\
	m_ref_count.fetch_add(1);\
	return m_ref_count;\
		}\
	\
	std::uint32_t Release() {\
		if (!m_ref_count.fetch_sub(1)) {\
			delete this;\
				}\
		return m_ref_count;\
		}\
	\
	const IObject* GetOwner() const {\
		return m_container.GetOwner();\
				}\
	IObject* GetOwner() {\
		return m_container.GetOwner();\
	}\
	\
	const Core::String ToString() const {\
		return #T;\
				}\
	\
	std::uint64_t GetType() {\
		return typeid(T).hash_code();\
				}\
	\
	void AddChild(IObject* object) {\
		m_container.AddChild(object);\
				}\
	\
	void RemoveChild(IObject* object, bool depth) {\
		m_container.RemoveChild(object, depth);\
				}\
	\
	void RemoveChild(std::uint32_t index) {\
		m_container.RemoveChild(index);\
				}\
	\
	IObject* GetChild(std::uint32_t index) {\
		return m_container.GetChild(index);\
				}\
	\
	const IObject* GetChild(std::uint32_t index) const {\
		return m_container.GetChild(index);\
				}\
	\
	std::uint32_t GetChildrenCount() const {\
		return m_container.GetChildrenCount();\
				}\
	private:\
	std::atomic<std::uint32_t> m_ref_count {1}; \
	Core::Container<IObject> m_container{this, Core::GetRootObject()};

}
PUNK_ENGINE_END

#endif	//	_H_IOBJECT