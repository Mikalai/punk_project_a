#ifndef _H_PUNK_VIRTUAL_KEY_BASED_MOTION_STRATEGY
#define _H_PUNK_VIRTUAL_KEY_BASED_MOTION_STRATEGY

#include "motion_strategy.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	class AnimationMixer;
}

namespace Attributes
{
	class KeyBasedMotionStrategy : public MotionStrategy
	{
		std::unique_ptr<AnimationMixer> m_Mixer;
		int64_t m_current_time_us;
	public:
		virtual void Save(Core::Buffer* buffer) const;
		virtual void Load(Core::Buffer* buffer);
        virtual bool GetLocalTransform(Math::mat4& value);
        virtual bool SetLocalTransform(const Math::mat4& value);
		virtual bool Update(int64_t current_time_us, int64_t delta_us);
		virtual ~KeyBasedMotionStrategy();
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_KEY_BASED_MOTION_STRATEGY
