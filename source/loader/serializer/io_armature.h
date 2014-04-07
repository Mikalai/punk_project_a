#ifndef IO_ARMATURE_H
#define IO_ARMATURE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    void SaveArmature(Core::Buffer *buffer, const Core::Object* o);
    void LoadArmature(Core::Buffer *buffer, Core::Object* o);
}
PUNK_ENGINE_END

#endif // IO_ARMATURE_H
