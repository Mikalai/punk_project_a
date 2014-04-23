#include <memory>
#include "light.h"
#include "lights/point_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti LightType{ "Attributes.Light", typeid(Light).hash_code(), { Core::Object::Type() } };

	Core::Rtti* Light::Type() {
		return &LightType;
	}


    Light::Light()
    {}

    Light::~Light()
    {}
}
PUNK_ENGINE_END
