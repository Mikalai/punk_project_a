#include <math/bounding_box.h>
#include "parser.h"
#include "parse_simple.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    bool ParseBoundingBox(Core::Buffer& buffer, Math::BoundingBox& value)
    {
		Parser* parser = GetDefaultParser();
        CHECK_START(buffer);
        Math::vec3 p[8];
		for (int i = 0; i < 8; ++i)
			parser->Parse(WORD_VEC3F, buffer, &p[i]);
        CHECK_END(buffer);
        return true;
    }
}
PUNK_ENGINE_END
