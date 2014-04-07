#ifndef _H_PUNK_VIRTUAL_LIGHT
#define _H_PUNK_VIRTUAL_LIGHT

#include <core/object.h>
#include <math/vec3.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class PUNK_ENGINE_API Light : public Core::Object
	{
	public:
        Light();
        Light(const Light&) = delete;
        Light& operator = (const Light&) = delete;
        virtual ~Light();

        PUNK_OBJECT(Light)
	};
}
PUNK_ENGINE_END

#endif
