#ifndef IO_HUMAN_ARMATURE_H
#define IO_HUMAN_ARMATURE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    void SaveHumanArmature(Core::Buffer *buffer, const Core::Object *o);
    void LoadHumanArmature(Core::Buffer *buffer, Core::Object *o);
    void SaveHumanMaleArmature(Core::Buffer *buffer, const Core::Object *o);
    void LoadHumanMaleArmature(Core::Buffer *buffer, Core::Object *o);
}
PUNK_ENGINE_END
#endif // IO_HUMAN_ARMATURE_H
