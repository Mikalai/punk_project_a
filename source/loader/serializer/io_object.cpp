#include <core/object.h>
#include <string/module.h>
#include "io_object.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveObject(Core::Buffer* buffer, const Core::Object* o) {
        buffer->WriteSigned64(o->GetType()->GetId());
    }

    void LoadObject(Core::Buffer *buffer, Core::Object* o) {
        //  do not read type. factory will do that
    }
}
PUNK_ENGINE_END
