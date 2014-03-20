#ifndef ABSTRACT_SHADOW_MAP_DEBUG_VISUALIZER_H
#define ABSTRACT_SHADOW_MAP_DEBUG_VISUALIZER_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class Frame;

    class AbstractShadowMapDebugVisualizer
    {
    public:
        virtual void Draw(Frame* frame) = 0;
    };
}
PUNK_ENGINE_END

#endif // ABSTRACT_SHADOW_MAP_DEBUG_VISUALIZER_H
