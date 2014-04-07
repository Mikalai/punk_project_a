#ifndef IO_MATERIAL_H
#define IO_MATERIAL_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    PUNK_ENGINE_API void SaveMaterial(Core::Buffer* buffer, const Core::Object* o);
    PUNK_ENGINE_API void LoadMaterial(Core::Buffer* buffer, Core::Object* o);
}
PUNK_ENGINE_END

#endif // IO_MATERIAL_H
