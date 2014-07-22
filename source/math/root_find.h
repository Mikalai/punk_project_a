#ifndef _H_PUNK_MATH_ROOT_FIND
#define _H_PUNK_MATH_ROOT_FIND

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Math {
	//	c[3]*x^3 + c[2]*x^2 + c[1]*x + c[0] = 0
	enum class RootFindResult
	{
		RESULT_NO_SOLUTION,
		RESULT_ONE_SOLUTION,
		RESULT_TWO_SOLUTIONS,
		RESULT_THREE_SOLUTIONS,
		RESULT_FOUR_SOLUTIONS
	};

	PUNK_ENGINE_API RootFindResult SolveQuadric(const float c[3], float out[2]);
	PUNK_ENGINE_API RootFindResult SolveCubic(const float c[4], float out[3]);
	PUNK_ENGINE_API RootFindResult SolveQuartic(const float c[5], float out[4]);

	PUNK_ENGINE_API RootFindResult SolveQuadric(const double c[3], double out[2]);
	PUNK_ENGINE_API RootFindResult SolveCubic(const double c[4], double out[3]);
	PUNK_ENGINE_API RootFindResult SolveQuartic(const double c[5], double out[4]);

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_ROOT_FIND
