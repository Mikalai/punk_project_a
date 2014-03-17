#ifndef SHADOW_MAP_RENDER_TYPE_H
#define SHADOW_MAP_RENDER_TYPE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics
{
    enum class ShadowMapRenderType { BadRender, SimpleRender, CascadeRender };

    const Core::String AsString(const ShadowMapRenderType& value);
}
PUNK_ENGINE_END

#endif // SHADOW_MAP_RENDER_TYPE_H
