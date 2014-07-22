#ifndef _H_MATH_TBN_SPACE
#define _H_MATH_TBN_SPACE

#include <config.h>
#include "tuple.h"
#include "matrix.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	void CalculateTBN(
		const Tuple<T, 3, tagPoint>& p1,
		const Tuple<T, 3, tagPoint>& p2, 
		const Tuple<T, 3, tagPoint>& p3,
		const Tuple<T, 2, tagPoint>& tex1, 
		const Tuple<T, 2, tagPoint>& tex2, 
		const Tuple<T, 2, tagPoint>& tex3,
		Tuple<T, 3, tagVector>& tng, 
		Tuple<T, 3, tagVector>& btn, 
		Tuple<T, 3, tagVector>& nrm, 
		T& mm)
	{
		nrm = Tuple<T, 3, tagVector>::CalculateNormal(p1, p2, p3);
		Matrix<T, 2, 2> s;
		s.at(0, 0) = (tex2 - tex1)[0];
		s.at(0, 1) = (tex2 - tex1)[1];
		s.at(1, 0) = (tex3 - tex1)[0];
		s.at(1, 1) = (tex3 - tex1)[1];

		Matrix<T, 2, 3> q;
		q.at(0, 0) = (p2 - p1)[0];
		q.at(0, 1) = (p2 - p1)[1];
		q.at(0, 2) = (p2 - p1)[2];
		q.at(1, 0) = (p3 - p1)[0];
		q.at(1, 1) = (p3 - p1)[1];
		q.at(1, 2) = (p3 - p1)[2];

		auto tb = s.Inversed() * q;

		tng[0] = tb.at(0, 0);
		tng[1] = tb.at(0, 1);
		tng[2] = tb.at(0, 2);

		btn[0] = tb.at(1, 0);
		btn[1] = tb.at(1, 1);
		btn[2] = tb.at(1, 2);

		if (btn.Length() == 0 || tng.Length() == 0) {
			nrm.Normalize();
			mm = 1;
		}
		else {
			//
			//	gram-shmidt normalization
			//
			nrm.Normalize();
			tng = (tng - tng.Dot(nrm)*nrm).Normalized();
			btn = (btn - btn.Dot(nrm)*nrm - btn.Dot(tng)*tng).Normalized();

			Matrix<T, 3, 3> m;
			m.at(0, 0) = tng[0]; m.at(0, 1) = tng[1]; m.at(0, 2) = tng[2];
			m.at(1, 0) = btn[0]; m.at(1, 1) = btn[1]; m.at(1, 2) = btn[2];
			m.at(2, 0) = nrm[0]; m.at(2, 1) = nrm[1]; m.at(2, 2) = nrm[2];

			mm = m.Determinant();/**/
		}
	}
}
PUNK_ENGINE_END

#endif	//	_H_MATH_TBN_SPACE