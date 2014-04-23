#ifndef IO_ANIMATION_MIXER_H
#define IO_ANIMATION_MIXER_H

#include <config.h>
#include <attributes/animation/animation_mixer.h>

PUNK_ENGINE_BEGIN
namespace Loader {
    PUNK_ENGINE_API void SaveAnimationMixer(Core::Buffer* buffer, const Core::Object* anim);
    PUNK_ENGINE_API void LoadAnimationMixer(Core::Buffer* buffer, Core::Object* anim);
}
PUNK_ENGINE_END

#endif // IO_ANIMATION_MIXER_H