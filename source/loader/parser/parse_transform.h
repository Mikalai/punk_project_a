#ifndef PARSE_TRANSFORM_H
#define PARSE_TRANSFORM_H

#include <config.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	class Transform;
}
namespace Loader {
	PUNK_ENGINE_LOCAL bool ParseTransform(Core::Buffer& buffer, Attributes::Transform* transform);
}
PUNK_ENGINE_END


#endif // PARSE_TRANSFORM_H
