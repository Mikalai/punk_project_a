#ifndef _H_LINEAR_EQUATION_SOLVER
#define _H_LINEAR_EQUATION_SOLVER

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {
	class mat4;
	class vec4;

	class PUNK_ENGINE_API LinearEquationSolver {
	public:
		static const Math::vec4 Solve(const Math::mat4& m, const Math::vec4& b);
	};
}
PUNK_ENGINE_END

#endif	//	 _H_LINEAR_EQUATION_SOLVER