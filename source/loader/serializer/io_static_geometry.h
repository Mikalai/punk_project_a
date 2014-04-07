#ifndef IO_STATIC_GEOMETRY_H
#define IO_STATIC_GEOMETRY_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    void SaveStaticGeometry(Core::Buffer *buffer, const Core::Object *o);
    void LoadStaticGeometry(Core::Buffer *buffer, Core::Object *o);
}
PUNK_ENGINE_END

#endif // IO_STATIC_GEOMETRY_H
