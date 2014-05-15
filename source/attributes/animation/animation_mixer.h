#ifndef _H_PUNK_UTILITY_ANIMATION_MixER
#define _H_PUNK_UTILITY_ANIMATION_MixER

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Attributes {

    class PUNK_ENGINE_API AnimationMixer : public Core::IObject
	{
	public:
        AnimationMixer();
        AnimationMixer(const AnimationMixer&) = delete;
        AnimationMixer& operator = (const AnimationMixer&) = delete;
		virtual ~AnimationMixer();

        virtual void SetTrackTime(float /*time*/) {}
        virtual float GetTrackTime() const {return 0;}
        virtual void SetLooping(size_t, bool) {}

        PUNK_OBJECT_DEFAULT_IMPL(AnimationMixer)
	};    
}
PUNK_ENGINE_END

#endif
