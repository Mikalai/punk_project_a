#ifndef _H_LINEAR_EQUATION_SOLVER
#define _H_LINEAR_EQUATION_SOLVER

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {

	struct tagVector;
	template<class T, int Rows, int Cols> class Matrix;
	template<class T, int Dim, typename tag> class Tuple;

	template<class T>
	class  LinearEquationSolver {
	public:
		static const Tuple<T, 4, tagVector> Solve(const Matrix<T, 4, 4>& m, const Tuple<T, 4, tagVector>& b) {
			auto inv_m = m.Inversed();
			auto x = inv_m * b;
			return x;
		}
	};
}
PUNK_ENGINE_END

#endif	//	 _H_LINEAR_EQUATION_SOLVER
