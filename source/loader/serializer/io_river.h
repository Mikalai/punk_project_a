#ifndef IO_RIVER_H
#define IO_RIVER_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    void SaveRiver(Core::Buffer *buffer, const Core::Object *o);
    void LoadRiver(Core::Buffer *buffer, Core::Object *o);
}
PUNK_ENGINE_END

#endif // IO_RIVER_H
