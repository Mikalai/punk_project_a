#include "animation_mixer.h"
#include "../../engine_objects.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    AnimationMixer::AnimationMixer()
		: m_container{ this, Core::GetRootObject() }
    {
    }

	AnimationMixer::~AnimationMixer()
    {
    }    
}
PUNK_ENGINE_END
