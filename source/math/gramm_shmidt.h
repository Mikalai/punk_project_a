#ifndef _H_GRAM_SHMIDT_NORMALIZATION
#define _H_GRAM_SHMIDT_NORMALIZATION

#include <config.h>
#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	class GrammShmidtNormalization {
	public:

		static void OrthogonalizeAndNormalize(
			Tuple<T, 3, tagVector>& a,
			Tuple<T, 3, tagVector>& b, 
			Tuple<T, 3, tagVector>& c) {

			a.Normalize();
			b = (b - b.Dot(a)*a).Normalized();
			c = (c - c.Dot(a)*a - c.Dot(b)*b).Normalized();
		}

		static void Orthogonalize(
			Tuple<T, 3, tagVector>& a, 
			Tuple<T, 3, tagVector>& b, 
			Tuple<T, 3, tagVector>& c) {

			b = (b - b.Dot(a)*a);
			c = (c - c.Dot(a)*a - c.Dot(b)*b);
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_GRAM_SHMIDT_NORMALIZATION