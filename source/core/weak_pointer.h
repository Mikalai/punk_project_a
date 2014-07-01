#ifndef _H_CORE_WEAK_PTR
#define _H_CORE_WEAK_PTR

#include <config.h>
#include "pointer.h"

PUNK_ENGINE_BEGIN
namespace Core {

	template<class T, class Base = IObject>
	class WeakPtr {
	public:
		template<class U, class B> friend class WeakPtr;

		WeakPtr(T*& ptr)
			: m_ptr{ ptr }
		{}

		WeakPtr(WeakPtr<T>& ptr)
			: m_ptr{ ptr.m_ptr }
		{}

		WeakPtr(Pointer<T>& ptr)
			: m_ptr{ ptr.m_object }
		{}

		T* operator-> () {
			return m_ptr;
		}

		const T* operator-> () const {
			return m_ptr;
		}

		T* Get() {
			return m_ptr;
		}

		const T* Get() const {
			return m_ptr;
		}

		Pointer<T, Base> Lock(void (*Destroy)(Base*)) {
			return Pointer < T, Base > {m_ptr, Destroy};
		}

	private:
		T*& m_ptr;
	};
}
PUNK_ENGINE_END

#endif	//_H_CORE_WEAK_PTR