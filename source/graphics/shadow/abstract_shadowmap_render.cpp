#include "abstract_shadowmap_render.h"
#include "cascade_shadow_map_render.h"
#include "simple_shadowmap_render.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    AbstractShadowMapRender* CreateShadowMapRender(const ShadowMapRenderType& value, IVideoDriver* driver)
    {
        switch(value)
        {
        case ShadowMapRenderType::CascadeRender:
            return new CascadeShadowMapRender(driver);
        case ShadowMapRenderType::SimpleRender:
            return new SimpleShadowMapRender(driver);
        default:
            return nullptr;
        }
    }
}
PUNK_ENGINE_END
