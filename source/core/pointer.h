#ifndef _H_CORE_UNIQUE_PTR
#define _H_CORE_UNIQUE_PTR

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
	
	class IObject;
	extern PUNK_ENGINE_API void DestroyObject(IObject* object);

	template<class T, class Base = IObject>	class WeakPtr;

	template<class T, class Base = IObject>
	class Pointer {
	public:
		template<class U, class B> friend class Pointer;
		template<class U, class B> friend class WeakPtr;

		Pointer()
			: m_object{ nullptr }
			, m_destroy{ nullptr }
		{}		

		Pointer(T* object, void(*destroy)(Base*) = DestroyObject)
			: m_object{ object }
			, m_destroy{ destroy }
		{
			if (m_object)
				m_object->AddRef();
		}

		template<class U>
		Pointer(const Pointer<U>& value) {
			m_object = dynamic_cast<T*>(value.m_object);
			if (m_object)
				m_object->AddRef();
			m_destroy = value.m_destroy;
		}

		template<class U>
		Pointer<T>& operator = (const Pointer<U>& value) {
			T* casted_value = dynamic_cast<T*>(value.m_object);
			if (m_object == casted_value)
				return *this;
			if (m_object)
				Destroy();
			m_object = casted_value;
			if (m_object)
				m_object->AddRef();
			m_destroy = value.m_destroy;
			return *this;
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
				return *this;
			Destroy();
			if (value.m_object)
				value.m_object->AddRef();
			m_object = value.m_object;
			m_destroy = value.m_destroy;
			return *this;
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

		const T* get() const {
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
            return m_object;
		}

		const T* operator * () const {
            return m_object;
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

	template<class T>
	inline bool operator < (const Core::Pointer<T>& l, const Core::Pointer<T>& r) {
		return l.get() < r.get();
	}

	template<class T>
	inline bool operator == (const Core::Pointer<T>& l, const Core::Pointer<T>& r) {
		return l.get() == r.get();
	}

	template<class T>
	inline bool operator != (const Core::Pointer<T>& l, const Core::Pointer<T>& r) {
		return l.get() != r.get();
	}

	template<class T, class U>
	inline bool operator != (const Core::Pointer<T>& l, const Core::Pointer<U>& r) {
		Core::Pointer<T> v = r;
		return v != l;
	}

	template<class T, class U>
	inline bool operator == (const Core::Pointer<T>& l, const Core::Pointer<U>& r) {
		Core::Pointer<T> v = r;
		return v == l;
	}

	template<class T> Core::Pointer<T> MakePtr(T* value) {
		return Core::Pointer < T > {value, Core::DestroyObject};
	}

	template<class T> struct Null {
		static Core::Pointer<T> Value() {
			return Core::Pointer < T > {(T*)nullptr, Core::DestroyObject};
		}
	};
}
PUNK_ENGINE_END

#endif
