#ifndef PARSE_ANYTHING_H
#define PARSE_ANYTHING_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
	class IObject;
	class Buffer;
}
namespace IoModule {
	extern Core::Pointer<Core::IObject> ParseAnything(Core::Buffer& buffer);
}
PUNK_ENGINE_END

#endif // PARSE_ANYTHING_H
