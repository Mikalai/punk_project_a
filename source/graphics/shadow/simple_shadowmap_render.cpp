#include <graphics/video_driver/module.h>
#include <graphics/texture/module.h>
#include <graphics/frame_buffer/module.h>
#include <graphics/render/module.h>
#include <graphics/frame/module.h>
#include <graphics/state/module.h>
#include <graphics/primitives/module.h>
#include "shadow_render_common.h"
#include "simple_shadowmap_render.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    SimpleShadowMapRender::SimpleShadowMapRender(IVideoDriver *driver)
        : m_driver(driver)
    {
        auto size = m_driver->GetSettings()->GetShadowMapSize();
        m_shadow_map = CreateTexture2D(size, size, Image::ImageFormat::DEPTH_COMPONENT32F,
                                                 Image::ImageFormat::DepthComponent,
                                                 Image::DataType::Float, 0, false, m_driver);

        m_shadow_map->SetCompareFunction(TextureCompareFunc::TextureLessEqual);
        m_shadow_map->SetCompareMode(TextureCompareMode::TextureNone);
        m_shadow_map->SetMinFilter(TextureFilter::Linear);
        m_shadow_map->SetMagFilter(TextureFilter::Linear);
        m_shadow_map->SetWrapMode(TextureWrapDirection::S, TextureWrapMode::ClampToEdge);
        m_shadow_map->SetWrapMode(TextureWrapDirection::R, TextureWrapMode::ClampToEdge);

        m_fb = CreateFrameBuffer(m_driver);
        m_fb->SetRenderTarget(FrameBufferTarget::TargetNone);
        m_fb->SetViewport(0, 0, size, size);
    }

    SimpleShadowMapRender::~SimpleShadowMapRender()
    {
        m_shadow_map.reset();
        m_fb.reset();
    }

    ITexture2D* SimpleShadowMapRender::GetShadowMap()
    {
        return m_shadow_map.get();
    }

    void SimpleShadowMapRender::Run(Batch** batches, std::uint32_t count)
    {
        IRenderUniquePtr render = CreateRender(m_driver);

        m_shadow_view = Math::CreateTargetCameraMatrix(m_light.GetPosition().XYZ(), m_light.GetPosition().XYZ() + m_light.GetDirection().XYZ(), {0, 0, 1});
        Math::FrustumTransform(m_frustum, m_cam_pos, m_cam_dir, m_cam_up);
        FindZRange(m_frustum, m_shadow_view, m_frame, m_z_range);
        m_shadow_proj = Math::CreateLightProjectionMatrix(m_z_range);
        m_shadow_crop = Math::CreateCropMatrix(m_frustum, m_shadow_view, m_shadow_proj, m_min_x, m_max_x, m_min_y, m_max_y);

        auto policy = IRenderContext::find(RenderPolicySet::DepthRender);
        policy->Begin();
        for (int i = 0; i < count; ++i)
        {
            Batch* b = batches[i];
            if (b->m_state->batch_state->m_cast_shadows) {
                //  create new batch
                Batch* batch = new Batch;
                batch->m_destroy = false;
                batch->m_renderable = b->m_renderable;
                batch->m_state = b->m_state->Clone(CoreState::ALL_STATES);

                //  setup batch
                batch->m_state->render_state->m_render_shadow_map = true;
                batch->m_state->render_state->m_shadow_model = ShadowModel::ShadowMapSimple;
                batch->m_state->view_state->m_projection = m_shadow_crop * m_shadow_proj;
                batch->m_state->view_state->m_view = m_shadow_view;
                batch->m_state->light_state->m_lights[0].SetShadowMatrix(0, m_shadow_crop * m_shadow_proj * m_shadow_view);
                //batch->m_state->light_state->m_lights[0].SetShadowMatrix(i, GetBiasMatrix() * m_shadow_proj[i] * m_shadow_view[i]);
                batch->m_state->texture_state->m_shadow_map = m_shadow_map.get();
                batch->m_state->texture_state->m_shadow_map_slot = 7;
                batch->m_state->light_state->m_lights[0].SetPosition(m_light.GetPosition().XYZ());
                batch->m_state->light_state->m_lights[0].SetDirection(m_light.GetDirection().XYZ());
                batch->m_state->light_state->m_lights[0].SetFarZ(m_z_range[1]);
                batch->m_state->light_state->m_lights[0].SetNearZ(m_z_range[0]);
                render->SubmitBatch(batch);
            }
        }        

        m_fb->AttachDepthTarget(m_shadow_map.get());
        m_fb->SetRenderTarget(Graphics::FrameBufferTarget::TargetNone);
        m_fb->SetClearFlag(false, true, false);
        m_fb->Clear();
        m_fb->SetPolygonOffset(1.0f, 4096.0f);
        render->AsyncBeginRendering(m_fb.get());
        render->WaitEndRendering();
    }

    void SimpleShadowMapRender::SetLight(const LightParameters& value)
    {
        m_light = value;
    }

    void SimpleShadowMapRender::SetViewProperties(float fov, float aspect, float n, float f,
                                                  const Math::vec3& center, const Math::vec3& dir, const Math::vec3& up)
    {
        m_frustum.fard = f;
        m_frustum.neard = n;
        m_frustum.fov = fov;
        m_frustum.ratio = aspect;
        m_cam_pos = center;
        m_cam_dir = dir;
        m_cam_up = up;
    }

    AbstractShadowMapDebugVisualizer* SimpleShadowMapRender::GetDebugVisualizer()
    {
        return nullptr;
    }

    IVideoDriver* SimpleShadowMapRender::GetVideoDriver()
    {
        return m_driver;
    }
}
PUNK_ENGINE_END
