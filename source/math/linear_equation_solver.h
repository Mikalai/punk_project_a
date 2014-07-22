#ifndef _H_LINEAR_EQUATION_SOLVER
#define _H_LINEAR_EQUATION_SOLVER

#include <config.h>
#include "mat4.h"
#include "vec4.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	class  LinearEquationSolver {
	public:
		const vec4 Solve(const mat4& m, const vec4& b) {
			auto inv_m = m.Inversed();
			auto x = inv_m * b;
			return x;
		}
	};
}
PUNK_ENGINE_END

#endif	//	 _H_LINEAR_EQUATION_SOLVER
