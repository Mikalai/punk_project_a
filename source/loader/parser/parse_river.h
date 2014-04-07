#ifndef PARSE_RIVER_H
#define PARSE_RIVER_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class Buffer; }
namespace Attributes { class River; }
namespace Loader {
    PUNK_ENGINE_LOCAL bool ParseRiver(Core::Buffer& buffer, Attributes::River& value);
}
PUNK_ENGINE_END

#endif // PARSE_RIVER_H
