#ifndef ABSOLUTE_VALUE_H
#define ABSOLUTE_VALUE_H

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	T Abs(const T& value) {
		return (value < 0 ? -value : value);
	}	

	template<class T>
	bool IsZero(T value) {
		return Abs(value) < Eps;
	}

	template<class T>
	bool AreEqual(T l, T r) {
		return IsZero(l - r);
	}
}
PUNK_ENGINE_END

#endif // ABSOLUTE_VALUE_H
