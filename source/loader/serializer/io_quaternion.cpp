#include "io_quaternion.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    PUNK_ENGINE_API void SaveQuaternion(Core::Buffer* buffer, const Math::quat& value) {
        for (int i = 0; i < 4; ++i)
            buffer->WriteReal32(value[i]);
    }

    PUNK_ENGINE_API void LoadQuaternion(Core::Buffer* buffer, Math::quat& value) {
        for (int i = 0; i < 4; ++i)
            value[i] = buffer->ReadReal32();
    }
}
PUNK_ENGINE_END
