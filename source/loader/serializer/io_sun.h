#ifndef IO_SUN_H
#define IO_SUN_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    void SaveSun(Core::Buffer *buffer, const Core::Object *o);
    void LoadSun(Core::Buffer *buffer, Core::Object *o);
}
PUNK_ENGINE_END

#endif // IO_SUN_H
