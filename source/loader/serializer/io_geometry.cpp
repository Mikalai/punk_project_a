#include "io_object.h"
#include "io_geometry.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveGeometry(Core::Buffer* buffer, const Core::Object* o)
    {
        SaveObject(buffer, o);
    }

    void LoadGeometry(Core::Buffer* buffer, Core::Object* o)
    {
        LoadObject(buffer, o);
    }
}
PUNK_ENGINE_END
