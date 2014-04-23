#include <core/module.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include "spot_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti SpotLightType{ "Attributes.SpotLight", typeid(SpotLight).hash_code(), { Light::Type() } };

	Core::Rtti* SpotLight::Type() {
		return &SpotLightType;
	}

    SpotLight::SpotLight()
    {
    }

    SpotLight::~SpotLight()
    {
    }
}
PUNK_ENGINE_END
