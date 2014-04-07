#ifndef PARSE_SPLINE_H
#define PARSE_SPLINE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Math { class Spline; }
namespace Loader {
    extern bool ParseSpline(Core::Buffer& buffer, Math::Spline& value);
}
PUNK_ENGINE_END

#endif // PARSE_SPLINE_H
