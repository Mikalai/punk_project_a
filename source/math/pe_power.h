#ifndef POWER_H
#define POWER_H

#include <config.h>
#include <math.h>

PUNK_ENGINE_BEGIN
namespace Math {

	inline float Pow(float value, float power) {
		return (float)pow(value, power);
	}

	inline double Pow(double value, double power) {
		return pow(value, power);
	}
}
PUNK_ENGINE_END

#endif // POWER_H
