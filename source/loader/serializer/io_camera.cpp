#include "io_camera.h"
#include "io_object.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveCamera(Core::Buffer* buffer, const Core::Object* value)
    {
        SaveObject(buffer, value);
    }

    void LoadCamera(Core::Buffer* buffer, Core::Object* value)
    {
        LoadObject(buffer, value);
    }
}
PUNK_ENGINE_END
