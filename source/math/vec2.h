#ifndef _H_PUNK_MATH_VEC2_MATH
#define _H_PUNK_MATH_VEC2_MATH

#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {

	using point2d = Tuple < float, 2, tagPoint > ;
	using vec2 = Tuple < float, 2, tagVector > ;	
	using ivec2 = Tuple < int, 2, tagVector > ;
	using ivec2v = std::vector < ivec2 > ;
	using vec2v = std::vector < vec2 > ;
}
PUNK_ENGINE_END

#endif  //  _H_PUNK_MATH_VEC2_MATH
