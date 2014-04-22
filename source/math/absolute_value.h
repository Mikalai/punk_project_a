#ifndef ABSOLUTE_VALUE_H
#define ABSOLUTE_VALUE_H

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Math {
	PUNK_ENGINE_API float Abs(float value);
	PUNK_ENGINE_API double Abs(double value);
	PUNK_ENGINE_API int Abs(int value);
}
PUNK_ENGINE_END

#endif // ABSOLUTE_VALUE_H
