#ifndef SIMPLE_SHADOWMAP_RENDER_H
#define SIMPLE_SHADOWMAP_RENDER_H

#include <graphics/lighting/module.h>
#include <graphics/texture/module.h>
#include <graphics/frame_buffer/module.h>
#include <math/frustum.h>
#include "abstract_shadowmap_render.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class IVideoDriver;
    class IFrameBuffer;

    class SimpleShadowMapRender : public AbstractShadowMapRender
    {
    public:
        SimpleShadowMapRender(IVideoDriver* driver);
        virtual ITexture2D* GetShadowMap() override;
        virtual void Run(Batch** batches, std::uint32_t count) override;
        virtual void SetLight(const LightParameters& value) override;
        virtual void SetViewProperties(float fov, float aspect, float n, float f, const Math::vec3& center, const Math::vec3& dir, const Math::vec3& up) override;
        virtual AbstractShadowMapDebugVisualizer* GetDebugVisualizer() override;
        virtual IVideoDriver* GetVideoDriver() override;
        virtual ~SimpleShadowMapRender();
    private:
        IVideoDriver* m_driver;
        ITexture2DUniquePtr m_shadow_map { nullptr, Core::DestroyObject };
        IFrameBufferUniquePtr m_fb {nullptr, Core::DestroyObject };
        LightParameters m_light;
        Math::FrustumCore m_frustum;
        Math::vec3 m_cam_pos;
        Math::vec3 m_cam_dir;
        Math::vec3 m_cam_up;
        Frame* m_frame;
        Math::vec2 m_z_range;
        Math::mat4 m_shadow_view;
        Math::mat4 m_shadow_proj;
        Math::mat4 m_shadow_crop;
        float m_min_x;
        float m_max_x;
        float m_min_y;
        float m_max_y;
    };
}
PUNK_ENGINE_END

#endif // SIMPLE_SHADOWMAP_RENDER_H
