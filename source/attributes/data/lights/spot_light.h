#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <attributes/data/light.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class SpotLight : public Light
    {
    public:
        SpotLight();
        SpotLight(const SpotLight&) = delete;
        SpotLight& operator = (const SpotLight&) = delete;
        virtual ~SpotLight();

    private:

        PUNK_OBJECT_DEFAULT_IMPL(SpotLight)
    };
}
PUNK_ENGINE_END

#endif // SPOT_LIGHT_H
