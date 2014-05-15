#ifndef _H_PUNK_VIRTUAL_LIGHT
#define _H_PUNK_VIRTUAL_LIGHT

#include <core/object.h>
#include <math/vec3.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class PUNK_ENGINE_API Light : public Core::IObject
	{
	public:
        Light();
        Light(const Light&) = delete;
        Light& operator = (const Light&) = delete;
        virtual ~Light();

        PUNK_OBJECT_DEFAULT_IMPL(Light)
	};
}
PUNK_ENGINE_END

#endif
