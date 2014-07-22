#ifndef ABSOLUTE_VALUE_H
#define ABSOLUTE_VALUE_H

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	T Abs(const T& value) {
		return (value < 0 ? -value : value);
	}	
}
PUNK_ENGINE_END

#endif // ABSOLUTE_VALUE_H
