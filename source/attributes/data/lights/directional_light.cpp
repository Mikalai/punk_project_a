#include <string/module.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include "directional_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti DirectionalLight::Type{"Attributes.DirectionalLight",
                                      typeid(DirectionalLight).hash_code(),
        {&Light::Type}};

    DirectionalLight::DirectionalLight()
    {
    }

    DirectionalLight::~DirectionalLight()
    {
    }    
}
PUNK_ENGINE_END
