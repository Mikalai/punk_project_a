#ifndef IO_ACTION_H
#define IO_ACTION_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Object;
    class Buffer;
}
namespace Loader {
    void SaveAction(Core::Buffer *buffer, const Core::Object *o);
    void LoadAction(Core::Buffer *buffer, Core::Object *o);
}
PUNK_ENGINE_END

#endif // IO_ACTION_H
