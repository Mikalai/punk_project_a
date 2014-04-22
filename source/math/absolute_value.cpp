#include <math.h>
#include "absolute_value.h"

PUNK_ENGINE_BEGIN
namespace Math {
	float Abs(float value) {
		return (value < 0 ? -value : value);
	}

	double Abs(double value) {
		return fabs(value);
	}

	int Abs(int value) {
		return (value < 0 ? -value : value);
	}
}
PUNK_ENGINE_END
