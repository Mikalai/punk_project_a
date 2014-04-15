#include <string/module.h>
#include <math/mat4.h>
#include "io_matrix.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveMatrix4f(Core::Buffer* buffer, const Math::mat4& value) {
        for (int i = 0; i < 16; ++i)
            buffer->WriteReal32(value[i]);
    }

    void LoadMatrix4f(Core::Buffer* buffer, Math::mat4& value) {
        for (int i = 0; i < 16; ++i)
            value[i] = buffer->ReadReal32();
    }
}
PUNK_ENGINE_END
