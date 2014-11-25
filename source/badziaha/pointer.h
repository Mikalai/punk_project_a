#ifndef _H_POINTER
#define _H_POINTER

#include <memory>

template<class T>
using TPtr = std::unique_ptr < T, void(*)(T*) >;

template<class T>
inline TPtr<T> make_ptr(T* value) {
	return TPtr < T > { value, destroy };
}

template<class T, class U>
inline TPtr<T> cast(TPtr<U>& v) {
	return make_ptr<T>(static_cast<T*>(v.release()));
}

#endif	//	_H_POINTER