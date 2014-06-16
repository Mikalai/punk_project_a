#ifndef IO_SPLINE_H
#define IO_SPLINE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
}
namespace Math {
    class Spline;
}
namespace IoModule {
    PUNK_ENGINE_API void SaveSpline(Core::Buffer* buffer, const Math::Spline& spline);
    PUNK_ENGINE_API void LoadSpline(Core::Buffer* buffer, Math::Spline& spline);
}
PUNK_ENGINE_END

#endif // IO_SPLINE_H
