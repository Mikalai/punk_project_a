#ifndef IO_GEOMETRY_H
#define IO_GEOMETRY_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    PUNK_ENGINE_API void SaveGeometry(Core::Buffer* buffer, const Core::Object* o);
    PUNK_ENGINE_API void LoadGeometry(Core::Buffer* buffer, Core::Object* o);
}
PUNK_ENGINE_END


#endif // IO_GEOMETRY_H
