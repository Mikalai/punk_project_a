#ifndef _H_PUNK_MATH_VEC4_MATH
#define _H_PUNK_MATH_VEC4_MATH

#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {

	using point4d = Tuple < float, 4, tagPoint >;
	using vec4 = Tuple < float, 4, tagVector >;
	using ivec4 = Tuple < int, 4, tagVector >;
	using ivec4v = std::vector < ivec4 >;
	using vec4v = std::vector < vec4 >;
}
PUNK_ENGINE_END

#endif  //  _H_PUNK_MATH_VEC4_MATH
