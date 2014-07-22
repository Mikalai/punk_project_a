#ifndef MIN_MAX_H
#define MIN_MAX_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	inline T Min(T x, T y) {
		return x < y ? x : y;
	}

	template<class T>
	inline T Max(T x, T y) {
		return x > y ? x : y;
	}

	template<class T>
	inline T Min(T a, T b, T c) {
		return Min(a, Min(b, c));
	}

	template<class T>
	inline T Max(T a, T b, T c) {
		return Max(a, Max(b, c));
	}
}
PUNK_ENGINE_END

#endif // MIN_MAX_H
