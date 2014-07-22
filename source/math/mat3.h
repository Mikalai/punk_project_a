/**********************************************************
*	File: mat3.h
*	Author: Mikalai Abramau
*	Desc: Implements a 3x3 matrix entity
***********************************************************/

#ifndef _H_MAT3X3_MATH
#define _H_MAT3X3_MATH

#include <initializer_list>
#include <array>
#include <config.h>
#include "matrix.h"

PUNK_ENGINE_BEGIN
namespace Math {
	using mat3 = Matrix < float, 3, 3 > ;
}
PUNK_ENGINE_END

#endif
