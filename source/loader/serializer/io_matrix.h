#ifndef IO_MATRIX_H
#define IO_MATRIX_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
}
namespace Math {
    class mat4;
}
namespace Loader {
    void SaveMatrix4f(Core::Buffer* buffer, const Math::mat4& value);
    void LoadMatrix4f(Core::Buffer* buffer, Math::mat4& value);
}
PUNK_ENGINE_END

#endif // IO_MATRIX_H
