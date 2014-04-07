#include <memory>
#include "light.h"
#include "lights/point_light.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    Core::Rtti Light::Type{"Attributes.Light",
                           typeid(Light).hash_code(),
        {&Core::Object::Type}};


    Light::Light()
    {}

    Light::~Light()
    {}
}
PUNK_ENGINE_END
