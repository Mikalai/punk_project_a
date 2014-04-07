#ifndef IO_ANIMATION_H
#define IO_ANIMATION_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    void SaveAnimation(Core::Buffer* buffer, const Core::Object* o);
    void LoadAnimation(Core::Buffer* buffer, Core::Object* o);
}
PUNK_ENGINE_END

#endif // IO_ANIMATION_H
