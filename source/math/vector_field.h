#ifndef _H_VECTOR_FIELD
#define _H_VECTOR_FIELD

#include <array>
#include <config.h>
#include "matrix.h"

PUNK_ENGINE_BEGIN
namespace Math {
	
	template<class T, int Dim> 
	class VectorField {
	public:

		Tuple<T, Dim, tagVector> 

	private:
		Matrix<T, Dim, Dim> m_matrix;
	};
}
PUNK_ENGINE_END

#endif  //  _H_PUNK_MATH_MAT2X2_MATH
