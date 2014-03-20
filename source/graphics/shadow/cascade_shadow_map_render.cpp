#include <math/module.h>
#include <graphics/texture/module.h>
#include <graphics/renderable/module.h>
#include <graphics/frame_buffer/module.h>
#include <graphics/render/module.h>
#include <graphics/frame/module.h>
#include <graphics/video_driver/module.h>
#include <graphics/render/module.h>
#include <graphics/state/module.h>
#include "shadow_render_common.h"
#include "cascade_shadow_map_render.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    CascadeShadowMapRender::Debug::Debug(CascadeShadowMapRender& m)
        : m_frustum(m.m_frustum)
        , m_shadow_view(m.m_shadow_view)
        , m_shadow_crop(m.m_shadow_crop)
        , m_shadow_mvp(m.m_shadow_mvp)
        , m_shadow_proj(m.m_shadow_proj)
        , m_projection(m.m_projection)
        , m_view(m.m_view)
    {}

    CascadeShadowMapRender::CascadeShadowMapRender(IVideoDriver* driver)
        : m_debug(*this)
        , m_driver(driver)
        , m_shadow_maps(nullptr, DestroyTexture2DArray)
        , m_fb(nullptr, DestroyFrameBuffer)
        , m_splits_count(4)
        , m_visualizer(new CascadeShadowMapDebugVisualizer(this))
    {
        auto size = m_driver->GetSettings()->GetShadowMapSize();
        m_shadow_maps = CreateTexture2DArray(size, size, m_splits_count,
                                             Image::ImageFormat::DEPTH_COMPONENT32F,
                                             Image::ImageFormat::DepthComponent,
                                             Image::DataType::Float, 0, false, m_driver);
        m_shadow_maps->SetCompareFunction(TextureCompareFunc::TextureLessEqual);
        m_shadow_maps->SetCompareMode(TextureCompareMode::TextureNone);
        m_shadow_maps->SetMinFilter(TextureFilter::Linear);
        m_shadow_maps->SetMagFilter(TextureFilter::Linear);
        m_shadow_maps->SetWrapMode(TextureWrapDirection::S, TextureWrapMode::ClampToEdge);
        m_shadow_maps->SetWrapMode(TextureWrapDirection::R, TextureWrapMode::ClampToEdge);

        m_fb = CreateFrameBuffer(m_driver);
        m_fb->SetRenderTarget(FrameBufferTarget::TargetNone);
        m_fb->SetViewport(0, 0, size, size);
    }

    CascadeShadowMapRender::~CascadeShadowMapRender()
    {
        m_shadow_maps.reset(nullptr);
        m_fb.reset(nullptr);
    }

    void CascadeShadowMapRender::SetLight(const LightParameters &value)
    {
        m_light = value;
    }

    void CascadeShadowMapRender::UpdateSplits(Math::FrustumCore frustum[MaxSplits], float n, float f)
    {
        float lambda = SplitWeight;
        float ratio = f/n;
        frustum[0].neard = n;

        for(int i=1; i != m_splits_count; i++)
        {
            float si = i / (float)m_splits_count;

            //  as i understood, this allows us to combine two methods of calculating
            //  near and far distance.
            //  1. nd + (fd - nd)*si. Based on linear division of the frustum space. But
            //  as i remember perpsective projection is not linear, thus
            //  fd/nd influences on accuracy alot, and as bigger this value more artifacts
            //  we will have due to limits of the depth buffer. That's why there is a second
            //  aproach based on non linear distances. As i understood the goal is to make
            //  less distance between fd and nd for near splits and bigger distance for
            //  far splits. This will make near shadow nicier than far, but who cares abour far
            //  shadow :)
            frustum[i].neard = lambda*(n*powf(ratio, si)) + (1.0f-lambda)*(n + (f - n)*si);
            frustum[i-1].fard = frustum[i].neard * 1.005f;
            //frustum[i-1].Update();
            //m_projection[i-1] = m_frustum[i-1].GetProjectionMatrix();
        }
        frustum[m_splits_count-1].fard = f;
        //frustum[m_splits_count-1].Update();
    }

    void CascadeShadowMapRender::Run(Batch** batches, std::uint32_t count)
    {
//        m_frame = frame;
//        auto batches = m_frame->GetBatches();
//        for (int i = 0; i < m_splits_count; ++i)
//        {
//            m_shadow_view[i] = Math::CreateTargetCameraMatrix(Math::vec3(0,0,0), m_light.GetDirection().XYZ().Normalized(), Math::vec3(-1, 0, 0));
//        }

//        UpdateSplits(m_frustum, m_near, m_far);

//        auto shadow_size = m_driver->GetSettings()->GetShadowMapSize();
//        m_fb->SetViewport(0, 0, shadow_size, shadow_size);
//        for (auto i = 0; i != m_splits_count; ++i)
//        {
//            //m_frustum[i].Update();
//            Math::FrustumTransform(m_frustum[i], m_cam_center, m_cam_dir, m_cam_up);

//            FindZRange(m_frustum[i], m_shadow_view[i], m_frame, m_z_range[i]);
//            m_shadow_proj[i] = Math::CreateLightProjectionMatrix(m_z_range[i]);
//            m_shadow_crop[i] = Math::CreateCropMatrix(m_frustum[i], m_shadow_view[i], m_shadow_proj[i], m_min_x[i], m_max_x[i], m_min_y[i], m_max_y[i]);

//            //m_shadow_proj[i] = CreateProjectionMatrix2(m_min_x[i], m_max_x[i], m_min_y[i], m_max_y[i], m_z_range[i][0], m_z_range[i][1]);

//            m_fb->AttachDepthTarget(m_shadow_maps.get(), i);
//            m_fb->SetRenderTarget(Graphics::FrameBufferTarget::TargetNone);
//            m_fb->Clear(false, true, false);
//            m_fb->Bind();
//            // m_fb->SetPolygonOffset(1.0f, 4096.0f);
//            auto policy = IRenderContext::find(RenderPolicySet::DepthRender);
//            policy->Begin();
//            for (Batch* batch : batches)
//            {

//                auto old_proj = batch->m_state->view_state->m_projection;
//                auto old_view = batch->m_state->view_state->m_view;
//                batch->m_state->view_state->m_projection = m_shadow_crop[i] * m_shadow_proj[i];
//                // batch->m_state->view_state->m_projection = m_shadow_proj[i];
//                batch->m_state->view_state->m_view = m_shadow_view[i];
//                batch->m_state->light_state->m_lights[0].SetShadowMatrix(i, m_shadow_crop[i] * m_shadow_proj[i] * m_shadow_view[i]);
//                //batch->m_state->light_state->m_lights[0].SetShadowMatrix(i, GetBiasMatrix() * m_shadow_proj[i] * m_shadow_view[i]);
//                float far_bound = 0.5f*(-m_frustum[i].fard * old_proj[10] + old_proj[14])/m_frustum[i].fard + 0.5f;
//                batch->m_state->light_state->m_lights[0].SetFarDistance(i, far_bound);
//                batch->m_state->texture_state->m_texture_array = m_shadow_maps.get();
//                batch->m_state->texture_state->m_texture_array_slot = 7;
//                batch->m_state->texture_state->m_texture_array_shadow_map_layer[i] = i;
//                batch->m_state->light_state->m_lights[0].SetPosition(m_light.GetPosition().XYZ());
//                batch->m_state->light_state->m_lights[0].SetDirection(m_light.GetDirection().XYZ());
//                batch->m_state->light_state->m_lights[0].SetFarZ(m_z_range[i][1]);
//                batch->m_state->light_state->m_lights[0].SetNearZ(m_z_range[i][0]);


//                policy->BindParameters(*batch->m_state);
//                batch->m_renderable->Bind(policy->GetRequiredAttributesSet());
//                batch->m_renderable->Render();
//                batch->m_renderable->Unbind();

//                //batch->m_state->view_state->m_projection = m_shadow_crop[i] * m_shadow_proj[i];
//                //batch->m_state->view_state->m_view = m_shadow_view[i];
//                batch->m_state->view_state->m_projection = old_proj;
//                batch->m_state->view_state->m_view = old_view;
//            }
//            m_fb->SetPolygonOffset(0, 0);
//            policy->End();
//            m_fb->Unbind();
//        }
    }

    ITexture* CascadeShadowMapRender::GetShadowMap()
    {
        return m_shadow_maps.get();
    }

    void CascadeShadowMapRender::SetViewProperties(float fov, float aspect, float n, float f, const Math::vec3 &center, const Math::vec3 &dir, const Math::vec3 &up)
    {
        m_cam_center = center;
        m_cam_dir = dir;
        m_cam_up = up;
        m_near = n;
        m_far = f;

        for (int i = 0; i != MaxSplits; ++i)
        {
            m_frustum[i].ratio = aspect;
            m_frustum[i].fov = fov + 0.2f;
            m_view[i] = Math::CreateTargetCameraMatrix(center, center + dir, up);
            m_projection[i] = Math::CreatePerspectiveProjection(fov, aspect, 1, m_near, m_far);
        }
    }

    int CascadeShadowMapRender::GetSplitCount() const
    {
        return m_splits_count;
    }

    void CascadeShadowMapRender::SetSplitCount(int value)
    {
        m_splits_count = value;
    }

    IVideoDriver* CascadeShadowMapRender::GetVideoDriver()
    {
        return m_driver;
    }

    AbstractShadowMapDebugVisualizer* CascadeShadowMapRender::GetDebugVisualizer()
    {
        return m_visualizer;
    }
}
PUNK_ENGINE_END
