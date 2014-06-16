#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <math/vec3.h>
#include "ilight.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	DECLARE_PUNK_GUID(IID_IDirectionalLight, "732C939A-544C-4F50-89BC-BC7889CBCD91");

    class IDirectionalLight : public ILight
    {
    public:        
		virtual const Math::vec3 GetDirection() const = 0;
		virtual void SetDirection(const Math::vec3& value) = 0;				
    };
}
PUNK_ENGINE_END

#endif // DIRECTIONAL_LIGHT_H
