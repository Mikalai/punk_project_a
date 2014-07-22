#ifndef _H_SYMMETRIC_EIGEN_SYSTEM
#define _H_SYMMETRIC_EIGEN_SYSTEM

#include <config.h>
#include "tuple.h"
#include "matrix.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	void SymmetricEigenSystem(const Matrix<T, 3, 3>& m, Tuple<T, 3, tagVector>& value, Matrix<T, 3, 3>& r)
	{
		const int max_sweep = 32;
		const T epsilon = 1.0e-10f;
		T m11 = m.at(0, 0);
		T m12 = m.at(0, 1);
		T m13 = m.at(0, 2);
		T m22 = m.at(1, 1);
		T m23 = m.at(1, 2);
		T m33 = m.at(2, 2);

		r.Identify();

		for (int a = 0; a < max_sweep; ++a)
		{
			if ((Abs(m12) < epsilon) && (Abs(m13) < epsilon) && (Abs(m23) < epsilon))
				break;

			//	annihilate 1 2
			if (m12 != T{0.0})
			{
				T u = (m22 - m11) * T{0.5} / m12;
				T u2 = u*u;
				T u2p1 = u2 + T{1.0};
				T t = (u2p1 != u2) ? ((u < T{0.0}) ? -T{1.0} : T{1.0}) * (sqrt(u2p1) - fabs(u)) : T{0.5} / u;
				T c = T{1.0} / sqrt(t*t + T{1.0});
				T s = c * t;

				m11 -= t * m12;
				m22 += t * m12;
				m12 = T{0.0};

				T temp = c*m13 - s * m23;
				m23 = s * m13 + c * m23;
				m13 = temp;

				for (int i = 0; i < 3; ++i)
				{
					T temp = c * r.at(i, 0) - s * r.at(i, 1);
					r.at(i, 1) = s * r.at(i, 0) + c * r.at(i, 1);
					r.at(i, 0) = temp;
				}
			}

			//	annihilate 1 3
			if (m13 != T{0.0})
			{
				T u = (m33 - m11) * T{0.5} / m13;
				T u2 = u*u;
				T u2p1 = u2 + T{1.0};
				T t = (u2p1 != u2) ? ((u < T{0.0}) ? -T{1.0} : T{1.0}) * (sqrt(u2p1) - fabs(u)) : T{0.5} / u;
				T c = T{1.0} / sqrt(t*t + T{1.0});
				T s = c * t;

				m11 -= t * m13;
				m33 += t * m13;
				m13 = T{0.0};

				T temp = c * m12 - s * m23;
				m23 = s * m12 + c * m23;
				m12 = temp;

				for (int i = 0; i < 3; ++i)
				{
					T temp = c * r.at(i, 0) - s * r.at(i, 2);
					r.at(i, 2) = s * r.at(i, 0) + c * r.at(i, 2);
					r.at(i, 0) = temp;
				}
			}

			//	annihilate 2 3
			if (m23 != T{0.0})
			{
				T u = (m33 - m22) * T{0.5} / m23;
				T u2 = u*u;
				T u2p1 = u2 + T{1.0};
				T t = (u2p1 != u2) ? ((u < T{0.0}) ? -T{1.0} : T{1.0}) * (sqrt(u2p1) - fabs(u)) : T{0.5} / u;
				T c = T{1.0} / sqrt(t*t + T{1.0});
				T s = c * t;

				m22 -= t * m23;
				m33 += t * m23;
				m23 = T{0.0};

				T temp = c * m12 - s * m13;
				m13 = s * m12 + c * m13;
				m12 = temp;

				for (int i = 0; i < 3; ++i)
				{
					T temp = c * r.at(i, 1) - s * r.at(i, 2);
					r.at(i, 2) = s * r.at(i, 1) + c * r.at(i, 2);
					r.at(i, 1) = temp;
				}
			}
		}
		value.Set(m11, m22, m33);
	}
}
PUNK_ENGINE_END

#endif	//	_H_SYMMETRIC_EIGEN_SYSTEM