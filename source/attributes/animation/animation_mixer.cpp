#include "animation_mixer.h"
#include "../../engine_objects.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti AnimationMixer::Type{L"Attributes.AnimationMixer",
                                    typeid(AnimationMixer).hash_code(),
        {&Core::Object::Type}};

    AnimationMixer::AnimationMixer()
    {
    }

	AnimationMixer::~AnimationMixer()
    {
    }    
}
PUNK_ENGINE_END
