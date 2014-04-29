#include "linear_equation_solver.h"
#include "vec4.h"
#include "mat4.h"

PUNK_ENGINE_BEGIN
namespace Math {
	const Math::vec4 LinearEquationSolver::Solve(const Math::mat4& m, const Math::vec4& b) {
		auto inv_m = m.Inversed();
		auto x = inv_m * b;		
		return x;
	}
}
PUNK_ENGINE_END