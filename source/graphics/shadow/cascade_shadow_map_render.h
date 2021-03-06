#ifndef SHADOW_MAP_RENDER_H
#define SHADOW_MAP_RENDER_H

#include <math/frustum.h>
#include <math/mat4.h>
#include <math/vec2.h>
#include <graphics/lighting/module.h>
#include <graphics/texture/module.h>
#include <graphics/frame_buffer/module.h>
#include "abstract_shadowmap_render.h"
#include "cascade_shadow_map_debug_visualizer.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class Frame;
    class IFrameBuffer;
    class IVideoDriver;

    class CascadeShadowMapRender : public AbstractShadowMapRender
    {
    public:
        static const int MaxSplits = 4;
        static constexpr float SplitWeight = 0.75f;

        CascadeShadowMapRender(IVideoDriver* driver);
        virtual ~CascadeShadowMapRender();
        virtual ITexture* GetShadowMap() override;
        virtual void Run(Batch** batches, std::uint32_t count) override;
        virtual void SetLight(const LightParameters& value) override;
        virtual void SetViewProperties(float fov, float aspect, float n, float f, const Math::vec3& center, const Math::vec3& dir, const Math::vec3& up) override;
        virtual AbstractShadowMapDebugVisualizer* GetDebugVisualizer() override;
        virtual IVideoDriver* GetVideoDriver() override;

        int GetSplitCount() const;
        void SetSplitCount(int value);

        struct Debug
        {
            Debug(CascadeShadowMapRender& m);

            Math::FrustumCore (&m_frustum)[MaxSplits];
            Math::mat4 (&m_shadow_view)[MaxSplits];
            Math::mat4 (&m_shadow_proj)[MaxSplits];
            Math::mat4 (&m_shadow_crop)[MaxSplits];
            Math::mat4 (&m_shadow_mvp)[MaxSplits];
            Math::mat4 (&m_projection)[MaxSplits];
            Math::mat4 (&m_view)[MaxSplits];
        };

        Debug m_debug;

    private:
        void UpdateSplits(Math::FrustumCore frustum[MaxSplits], float n, float f);

    private:
        ITexture2DArrayUniquePtr m_shadow_maps;
        Frame* m_frame;
        LightParameters m_light;
        IFrameBufferUniquePtr m_fb;
        Math::FrustumCore m_frustum[MaxSplits];
        Math::mat4 m_projection[MaxSplits];
        Math::mat4 m_view[MaxSplits];
        Math::vec3 m_cam_center;
        Math::vec3 m_cam_dir;
        Math::vec3 m_cam_up;
        Math::mat4 m_shadow_view[MaxSplits];
        Math::mat4 m_shadow_proj[MaxSplits];
        Math::mat4 m_shadow_crop[MaxSplits];
        Math::mat4 m_shadow_mvp[MaxSplits];
        Math::vec2 m_z_range[MaxSplits];
        float m_min_x[MaxSplits];
        float m_max_x[MaxSplits];
        float m_min_y[MaxSplits];
        float m_max_y[MaxSplits];
        int m_splits_count;
        IVideoDriver* m_driver;
        float m_near;
        float m_far;

        friend struct Debug;
        CascadeShadowMapDebugVisualizer* m_visualizer;
    };
}
PUNK_ENGINE_END

#endif // SHADOW_MAP_RENDER_H
