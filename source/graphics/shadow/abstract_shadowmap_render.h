#ifndef ABSTRACT_SHADOWMAP_RENDER_H
#define ABSTRACT_SHADOWMAP_RENDER_H

#include <cstdint>
#include <math/mat4.h>
#include "shadow_map_render_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class IVideoDriver;
    class ITexture;
    class Frame;
    struct LightParameters;
    class Batch;
    class AbstractShadowMapDebugVisualizer;

    class AbstractShadowMapRender
    {
    public:
        virtual ITexture* GetShadowMap() = 0;
        virtual void Run(Batch** batches, std::uint32_t count) = 0;
        virtual void SetLight(const LightParameters& value) = 0;
        virtual void SetViewProperties(float fov, float aspect, float n, float f, const Math::vec3& center, const Math::vec3& dir, const Math::vec3& up) = 0;
        virtual AbstractShadowMapDebugVisualizer* GetDebugVisualizer() = 0;
        virtual IVideoDriver* GetVideoDriver() = 0;
    };

    PUNK_ENGINE_API AbstractShadowMapRender* CreateShadowMapRender(const ShadowMapRenderType& value, IVideoDriver* driver);
}
PUNK_ENGINE_END

#endif // ABSTRACT_SHADOWMAP_RENDER_H
