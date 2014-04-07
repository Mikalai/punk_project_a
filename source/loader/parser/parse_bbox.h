#ifndef PARSE_BBOX_H
#define PARSE_BBOX_H

#include <config.h>
PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Math { class BoundingBox; }
namespace Loader {
    extern bool ParseBoundingBox(Core::Buffer& buffer, Math::BoundingBox& value);
}
PUNK_ENGINE_END


#endif // PARSE_BBOX_H
