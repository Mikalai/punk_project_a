#ifndef _H_QUAT_MATH
#define _H_QUAT_MATH

#include <initializer_list>
#include <array>
#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {
	using quat = Tuple < float, 4, tagQuaternion > ;
}
PUNK_ENGINE_END

#endif	//	_H_QUAT_MATH
