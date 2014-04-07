#ifndef PARSE_MAP_DESCRIPTION_H
#define PARSE_MAP_DESCRIPTION_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Attributes { class Terrain; }
namespace Core { class Buffer; }
namespace Loader {
    extern bool ParseMapDescription(Core::Buffer& buffer, Attributes::Terrain* terrain);
}
PUNK_ENGINE_END

#endif // PARSE_MAP_DESCRIPTION_H
