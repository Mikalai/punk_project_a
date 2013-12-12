#ifndef _H_PUNK_MATH_REGION
#define _H_PUNK_MATH_REGION

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Math
{
	template<class T> class Vector3;

	class Region
	{
	public:
		virtual bool IsPointIn(const Vector3<float>& point) override;
	}
}
PUNK_ENGINE_END

#endif