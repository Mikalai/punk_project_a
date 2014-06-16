#ifndef IO_SOUND_H
#define IO_SOUND_H

#include <config.h>
#include <attributes/sound.h>

PUNK_ENGINE_BEGIN
namespace IoModule {
    PUNK_ENGINE_API void SaveSound(Core::Buffer* buffer, const Attributes::Sound* value);
    PUNK_ENGINE_API void LoadSound(Core::Buffer* buffer, Attributes::Sound* value);
}
PUNK_ENGINE_END

#endif // IO_SOUND_H
