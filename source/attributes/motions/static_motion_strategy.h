#ifndef _H_PUNK_VIRTUAL_STATIC_MOTION_STRATEGY
#define _H_PUNK_VIRTUAL_STATIC_MOTION_STRATEGY

#include <cstdint>
#include <math/mat4.h>
#include <math/vec3.h>
#include "motion_strategy.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class PUNK_ENGINE_API StaticMotionStrategy : public MotionStrategy
	{
	public:
		StaticMotionStrategy();
		void SetAffineMatrix(const Math::mat4& matrix);
		const Math::mat4& GetAffineMatrix() const;
		Math::mat4& GetAffineMatrix();
        virtual bool Update(int64_t, int64_t) { return true; }
		virtual ~StaticMotionStrategy();
	private:
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_STATIC_MOTION_STRATEGY
