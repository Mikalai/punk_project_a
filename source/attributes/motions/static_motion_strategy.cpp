#include "static_motion_strategy.h"
#include "../data/transform.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	StaticMotionStrategy::StaticMotionStrategy()
		: MotionStrategy()
	{
		SetMotionStrategyType(MotionStrategyType::MOTION_STRATEGY_TYPE_STATIC);
	}

	void StaticMotionStrategy::SetAffineMatrix(const Math::mat4& matrix)
	{
		GetTransform()->Set(matrix);
	}
	
	const Math::mat4& StaticMotionStrategy::GetAffineMatrix() const
	{
		return GetTransform()->Get();
	}

	Math::mat4& StaticMotionStrategy::GetAffineMatrix() 
	{
		return GetTransform()->Get();
	}

	StaticMotionStrategy::~StaticMotionStrategy()
	{
	}
}
PUNK_ENGINE_END
