#ifndef IO_OBJECT_H
#define IO_OBJECT_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Object;
    class Buffer;
}
namespace Loader {
    void SaveObject(Core::Buffer* buffer, const Core::Object* o);
    void LoadObject(Core::Buffer *buffer, Core::Object* o);
}
PUNK_ENGINE_END

#endif // IO_OBJECT_H
