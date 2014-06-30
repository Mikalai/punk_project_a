#include <system/factory/module.h>
#include <graphics/error/module.h>
#include <graphics/renderable/module.h>
#include <graphics/render/irender_context.h>
#include <graphics/video_driver/module.h>
#include <graphics/state/module.h>
#include <graphics/texture/module.h>
#include <graphics/primitives/irenderable.h>
#include "render_pass.h"
#include "render_batch.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    RenderPass::RenderPass(IVideoDriver* driver, std::vector<Batch*> batches)
		: m_driver(driver)
		, m_batches(batches)
	{}

	RenderPass::~RenderPass()
	{
		for (auto b : m_batches)
		{
			delete b;
		}
		m_batches.clear();
	}

	void RenderPass::SetUpShadowMap()
    {
        auto w = m_driver->GetSettings()->GetShadowMapSize();
        auto h = m_driver->GetSettings()->GetShadowMapSize();
        if (!m_shadow_map) {
			m_shadow_map = System::CreateInstance<ITexture2D>(IID_ITexture2D);
            if (m_shadow_map)
				m_shadow_map->Initialize(w, h, ImageModule::ImageFormat::DEPTH_COMPONENT16, nullptr, false, m_driver);
        }
        else {
            m_shadow_map->Resize(w, h);
        }
//		m_driver->SetRenderTarget(nullptr, m_shadow_map);
//		m_driver->Clear(true, true, true);
    }

    void RenderObject(Batch* b)
    {
		for (LightParameters p : b->m_state->light_state->m_lights)
        {
			//std::unique_ptr<CoreState> state(b->m_state->Clone());
        }
    }

	void RenderPass::GenerateShadowMap(std::vector<Batch*>& batches)
    {
//        SetUpShadowMap();
//        for (Batch* b : batches)
//        {
//			if (b->m_state->batch_state->m_cast_shadows)
//            {
//                RenderObject(b);
//            }
//        }
////		m_driver->SetRenderTarget(nullptr, nullptr);
    }


    void RenderPass::OnePass(IRenderable* renderable, CoreState* state)
    {
        TextureContext tc;
        IRenderContext* policy = nullptr;///Sele(state);

        if (policy)
        {
       //     tc.Bind();
            policy->Begin();
            policy->ApplyState(*state);
            renderable->Bind();
            renderable->LowLevelRender();
            renderable->Unbind();
            policy->End();
       //     tc.Unbind();
        }

    }

	void RenderPass::Run()
	{        
        //	Process batches: find all shadow casters
		//	Process batches: split batches on light groups
		//	Process batches: for each light group generate shadow map
		//	Process batches: for each light group using shadow map render final scene

        for (Batch* batch : m_batches)
		{
            OnePass(batch->m_renderable.get(), batch->m_state);
		}
	}
}
PUNK_ENGINE_END
