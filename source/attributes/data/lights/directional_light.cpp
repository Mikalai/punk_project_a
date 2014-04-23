#include <string/module.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include "directional_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti DirectionalLightType{ "Attributes.DirectionalLight", typeid(DirectionalLight).hash_code(), { Light::Type() } };

	Core::Rtti* DirectionalLight::Type() {
		return &DirectionalLightType;
	}

    DirectionalLight::DirectionalLight()
    {
    }

    DirectionalLight::~DirectionalLight()
    {
    }    
}
PUNK_ENGINE_END
