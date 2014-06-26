#ifndef _H_CORE_UNIQUE_PTR
#define _H_CORE_UNIQUE_PTR

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {

	class IObject;

	template<class T, class Base = IObject>
	class Pointer {
	public:
		Pointer(T* object, void(*destroy)(Base*))
			: m_object{ object }
			, m_destroy{ destroy }
		{
			if (m_object)
				m_object->AddRef();
		}

		Pointer(const Pointer<T, Base>& value)
			: m_object{ value.m_object }
			, m_destroy{ value.m_destroy }
		{
			if (m_object)
				m_object->AddRef();
		}

		Pointer(Pointer<T, Base>&& value)
			: m_object{ value.m_object }
			, m_destroy{ value.m_destroy }
		{
			value.m_object = nullptr;
		}

		Pointer<T>& operator = (const Pointer<T, Base>& value) {
			if (m_object == value.m_object)
				return;
			Destroy();
			if (value.m_object)
				value.m_object->AddRef();
			m_object = value.m_object;
			m_destroy = value.m_destroy;
			return this;
		}

		Pointer<T>& operator = (Pointer<T, Base>&& value) {
			if (m_object == value.m_object)
				return *this;
			Destroy();

			m_object = value.m_object;
			m_destroy = value.m_destroy;
			value.m_object = nullptr;
			return *this;
		}

		T* get() {
			return m_object;
		}

		operator bool() {
			return m_object != nullptr;
		}

		T* release() {
			auto result = m_object;
			m_object = nullptr;
			return result;
		}

		void reset(T* value) {
			Destroy();
			m_object = value;
			if (m_object)
				m_object->AddRef();
		}

		T* operator -> () {
			return m_object;
		}

		const T* operator -> () const {
			return m_object;
		}

		T* operator * () {
			return m_object
		}

		const T* operator * () const {
			return m_object
		}

		~Pointer() {
			Destroy();
		}

	private:
		void Destroy() {
			if (m_object && m_destroy)
				m_destroy(m_object);
		}

		T* m_object{ nullptr };
		void(*m_destroy)(Base*){ nullptr };
	};
}
PUNK_ENGINE_END

#endif