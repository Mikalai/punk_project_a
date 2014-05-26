#include <string/module.h>
#include "io_string.h"

PUNK_ENGINE_BEGIN
namespace IoModule {
    void SaveString(Core::Buffer* buffer, const Core::String& value) {
        buffer->WriteString(value);
    }

    void LoadString(Core::Buffer* buffer, Core::String& value) {
        value = buffer->ReadString();
    }
}
PUNK_ENGINE_END
