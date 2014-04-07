#ifndef IO_CAMERA_H
#define IO_CAMERA_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
    class Object;
}
namespace Loader {
    void SaveCamera(Core::Buffer* buffer, const Core::Object* value);
    void LoadCamera(Core::Buffer* buffer, Core::Object* value);
}
PUNK_ENGINE_END


#endif // IO_CAMERA_H
