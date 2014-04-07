#ifndef PARSE_ANYTHING_H
#define PARSE_ANYTHING_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Object;
    class Buffer;
}
namespace Loader {
extern Core::Object* ParseAnything(Core::Buffer& buffer);
}
PUNK_ENGINE_END

#endif // PARSE_ANYTHING_H
