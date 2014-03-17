#include <string/string.h>
#include "shadow_map_render_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    const Core::String AsString(const ShadowMapRenderType& value)
    {
        switch(value)
        {
        case ShadowMapRenderType::SimpleRender:
            return L"SimpleShadowMapRender";
        case ShadowMapRenderType::CascadeRender:
            return L"CascadeShadowMapRender";
        case ShadowMapRenderType::BadRender:
        default:
            return L"BadShadowRender";
        }
    }
}
PUNK_ENGINE_END
