#ifndef CASCADE_SHADOW_MAP_DEBUG_VISUALIZER_H
#define CASCADE_SHADOW_MAP_DEBUG_VISUALIZER_H

#include "abstract_shadow_map_debug_visualizer.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class CascadeShadowMapRender;

    class CascadeShadowMapDebugVisualizer : public AbstractShadowMapDebugVisualizer
    {
    public:
        CascadeShadowMapDebugVisualizer(CascadeShadowMapRender* render);
        virtual void Draw(IFrame *frame) override;
    private:
        CascadeShadowMapRender* m_shadow_map_render;
    };
}
PUNK_ENGINE_END

#endif // CASCADE_SHADOW_MAP_DEBUG_VISUALIZER_H
