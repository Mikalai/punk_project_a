#ifndef SQUARE_ROOT_H
#define SQUARE_ROOT_H

#include <config.h>
#include <math.h>

PUNK_ENGINE_BEGIN
namespace Math {

	inline float Sqrt(float value) {		
		return sqrtf(value);
	}

	inline double Sqrt(double value) {
		return sqrt(value);
	}
}
PUNK_ENGINE_END

#endif // SQUARE_ROOT_H
