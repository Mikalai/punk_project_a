#ifndef PARSE_ANIMATION_H
#define PARSE_ANIMATION_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
}
namespace Attributes {
    class Animation;
}
namespace Loader {
    extern bool ParseAnimation(Core::Buffer& buffer, Attributes::Animation* animation);
}
PUNK_ENGINE_END

#endif // PARSE_ANIMATION_H
