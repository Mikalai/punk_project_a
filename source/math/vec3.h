#ifndef _H_PUNK_MATH_VEC3_MATH
#define _H_PUNK_MATH_VEC3_MATH

#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {

	using vec3 = Tuple < float, 3, tagVector >;
	using point3d = Tuple < float, 3, tagPoint > ;
	using ivec3 = Tuple < int, 3, tagVector >;
	using ivec3v = std::vector < ivec3 >;
	using vec3v = std::vector < vec3 >;
}
PUNK_ENGINE_END

#endif  //  _H_PUNK_MATH_VEC3_MATH
