#include <graphics/renderable/module.h>
#include <graphics/render/render_context/irender_context.h>
#include <graphics/video_driver/module.h>
#include <graphics/state/module.h>
#include <graphics/texture/module.h>
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
		auto w = m_driver->GetConfig().shadow_map_width;
		auto h = m_driver->GetConfig().shadow_map_height;
        if (!m_shadow_map)
        {
			m_shadow_map = m_driver->CreateTexture2D(w, h, ImageModule::IMAGE_FORMAT_DEPTH_COMPONENT16, nullptr, false);
        }
        else
        {
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

    /**
     * @brief BindTexture
     * @param state
     * @return True if texture 2d array is used, false otherwise
     */
    bool BindTexture(CoreState* state)
    {
        if (state->render_state->m_enable_texture)
        {
            if (state->texture_state->m_texture_array && state->texture_state->m_texture_array_slot != -1)
            {
                state->texture_state->m_texture_array->Bind(state->texture_state->m_texture_array_slot);
                for (int i = 0; i != 4; ++i)
                    if (state->texture_state->m_diffuse_map[i] && state->texture_state->m_diffuse_slot[0] != -1)
                        state->texture_state->m_diffuse_map[i]->Bind(state->texture_state->m_diffuse_slot[i]);
                if (state->texture_state->m_height_map && state->texture_state->m_height_map_slot != -1)
                    state->texture_state->m_height_map->Bind(state->texture_state->m_height_map_slot);
                if (state->texture_state->m_normal_map && state->texture_state->m_normal_map_slot != -1)
                    state->texture_state->m_normal_map->Bind(state->texture_state->m_normal_map_slot);
                if (state->texture_state->m_shadow_map && state->texture_state->m_shadow_map_slot != -1)
                    state->texture_state->m_shadow_map->Bind(state->texture_state->m_shadow_map_slot);
                if (state->texture_state->m_text_map && state->texture_state->m_text_map_slot != -1)
                    state->texture_state->m_text_map->Bind(state->texture_state->m_text_map_slot);
                return true;
            }
            else
            {
                for (int i = 0; i != 4; ++i)
                    if (state->texture_state->m_diffuse_map[i] && state->texture_state->m_diffuse_slot[0] != -1)
                        state->texture_state->m_diffuse_map[i]->Bind(state->texture_state->m_diffuse_slot[i]);
                if (state->texture_state->m_height_map && state->texture_state->m_height_map_slot != -1)
                    state->texture_state->m_height_map->Bind(state->texture_state->m_height_map_slot);
                if (state->texture_state->m_normal_map && state->texture_state->m_normal_map_slot != -1)
                    state->texture_state->m_normal_map->Bind(state->texture_state->m_normal_map_slot);
                if (state->texture_state->m_shadow_map && state->texture_state->m_shadow_map_slot != -1)
                    state->texture_state->m_shadow_map->Bind(state->texture_state->m_shadow_map_slot);
                if (state->texture_state->m_text_map && state->texture_state->m_text_map_slot != -1)
                    state->texture_state->m_text_map->Bind(state->texture_state->m_text_map_slot);
                return false;
            }
        }
        return false;
    }

    bool BindNormalMap(CoreState* state)
    {
        if (state)
        {
            if (state->texture_state->m_normal_map && state->texture_state->m_normal_map_slot != -1)
            {
                state->texture_state->m_normal_map->Bind(state->texture_state->m_normal_map_slot);
                return true;
            }
        }
        return false;
    }

    IRenderContext* RenderDepth(CoreState* state)
    {
        if (state->render_state->m_enable_skinning)
        {
            return IRenderContext::find(RenderPolicySet::DepthRenderSkinning);
        }
        else
        {
            return IRenderContext::find(RenderPolicySet::DepthRender);
        }
    }

    IRenderContext* RenderTerrain(CoreState* state)
    {
        if (BindTexture(state))
            ;
        else
            return IRenderContext::find(RenderPolicySet::Terrain);
        return nullptr;
    }

    IRenderContext* RenderLightingWithShadowsSimpleTextured(CoreState* state)
    {
        BindTexture(state);
        if (state->render_state->m_enable_diffuse_shading)
        {
            if (state->light_state->m_light_model == LightModel::BumpMappingDiffuse)
            {
                if (state->render_state->m_enable_specular_shading)
                {
                    if (state->render_state->m_enable_skinning)
                        return IRenderContext::find(RenderPolicySet::BumpMappingTextureDiffuseSpecularSkinningShadowingSimple);
                    else
                        return IRenderContext::find(RenderPolicySet::BumpMappingTextureDiffuseSpecularShadowingSimple);
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return IRenderContext::find(RenderPolicySet::BumpMappingTextureDiffuseSkinningShadowingSimple);
                    else
                        return IRenderContext::find(RenderPolicySet::BumpMappingTextureDiffuseShadowingSimple);
                }
            }
            else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
            {
                if (state->render_state->m_enable_specular_shading)
                {
                    if (state->render_state->m_enable_skinning)
                        return IRenderContext::find(RenderPolicySet::LightPerFragmentTextureDiffuseSpecularSkinningShadowingSimple);
                    else
                        return IRenderContext::find(RenderPolicySet::LightPerFragmentTextureDiffuseSpecularShadowingSimple);
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return IRenderContext::find(RenderPolicySet::LightPerFragmentTextureDiffuseSkinningShadowingSimple);
                    else
                        return IRenderContext::find(RenderPolicySet::LightPerFragmentTextureDiffuseShadowingSimple);
                }
            }
            else if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
            {
                if (state->render_state->m_enable_specular_shading)
                {
                    if (state->render_state->m_enable_skinning)
                        return IRenderContext::find(RenderPolicySet::LightPerVertexTextureDiffuseSpecularSkinningShadowingSimple);
                    else
                        return IRenderContext::find(RenderPolicySet::LightPerVertexTextureDiffuseSpecularShadowingSimple);
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return IRenderContext::find(RenderPolicySet::LightPerVertexTextureDiffuseSkinningShadowingSimple);
                    else
                        return IRenderContext::find(RenderPolicySet::LightPerVertexTextureDiffuseShadowingSimple);
                }
            }
        }
        return nullptr;
    }

    IRenderContext* RenderLightingWithShadowsSimpleSolid(CoreState* state)
    {
        if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
        {
            if (state->render_state->m_shadow_model == ShadowModel::ShadowMapSimple)
            {
                return IRenderContext::find(RenderPolicySet::LightPerVertexDiffuseShadowingSimple);
            }
            else if (state->render_state->m_shadow_model == ShadowModel::ShadowMapCascade)
            {
                return IRenderContext::find(RenderPolicySet::LightPerVertexDiffuseShadowingCascade);
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_shadow_model == ShadowModel::ShadowMapSimple)
            {
                return IRenderContext::find(RenderPolicySet::LightPerFragmentDiffuseShadowingSimple);
            }
            else if (state->render_state->m_shadow_model == ShadowModel::ShadowMapCascade)
            {
                return IRenderContext::find(RenderPolicySet::LightPerFragmentDiffuseShadowingCascade);
            }
        }
        return nullptr;
    }

    IRenderContext* RenderLightingWithShadowsCascadeTextured(CoreState* state)
    {
        return nullptr;
    }

    IRenderContext* RenderLightingWithShadowsCascadeSolid(CoreState* state)
    {
        return nullptr;
    }

    IRenderContext* RenderLightingWithShadows(CoreState* state)
    {
        if (state->render_state->m_shadow_model == ShadowModel::ShadowMapSimple)
        {
            if (state->render_state->m_enable_texture)
            {
                return RenderLightingWithShadowsSimpleTextured(state);
            }
            else
            {
                return RenderLightingWithShadowsSimpleSolid(state);
            }
        }
        else if (state->render_state->m_shadow_model == ShadowModel::ShadowMapCascade)
        {
            if (state->render_state->m_enable_texture)
            {
                return RenderLightingWithShadowsCascadeTextured(state);
            }
            else
            {
                return RenderLightingWithShadowsCascadeSolid(state);
            }
        }
    }

    IRenderContext* RenderLightingWithoutShadowsTextured(CoreState* state)
    {
        BindTexture(state);
        if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::LightPerVertexTextureDiffuseSpecularSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::LightPerVertexTextureDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::LightPerVertexTextureDiffuseSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::LightPerVertexTextureDiffuse);
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::LightPerFragmentTextureDiffuseSpecularSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::LightPerFragmentTextureDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::LightPerFragmentTextureDiffuseSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::LightPerFragmentTextureDiffuse);
            }
        }
        else if (state->light_state->m_light_model == LightModel::BumpMappingDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::BumpMappingTextureDiffuseSpecularSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::BumpMappingTextureDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::BumpMappingTextureDiffuseSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::BumpMappingTextureDiffuse);
            }
        }
        return nullptr;
    }

    IRenderContext* RenderLightingWithoutShadowsSolid(CoreState* state)
    {
        if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
        {            
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::LightPerVertexDiffuseSpecularSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::LightPerVertexDiffuseSpecular);
            }
            else
            {
            if (state->render_state->m_enable_skinning)
                return IRenderContext::find(RenderPolicySet::LightPerVertexDiffuseSkinning);
            else
                return IRenderContext::find(RenderPolicySet::LightPerVertexDiffuse);
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::LightPerFragmentDiffuseSpecularSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::LightPerFragmentDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::LightPerFragmentDiffuseSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::LightPerFragmentDiffuse);
            }
        }
        else if (state->light_state->m_light_model == LightModel::BumpMappingDiffuse)
        {
            BindNormalMap(state);
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::BumpMappingDiffuseSpecularSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::BumpMappingDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return IRenderContext::find(RenderPolicySet::BumpMappingDiffuseSkinning);
                else
                    return IRenderContext::find(RenderPolicySet::BumpMappingDiffuse);
            }
        }
        return nullptr;
    }

    IRenderContext* RenderLightingWithoutShadows(CoreState *state)
    {
        if (state->render_state->m_enable_texture)
        {
            if (state->render_state->m_enable_diffuse_shading)
            {
                return RenderLightingWithoutShadowsTextured(state);
            }
        }
        else
        {
            if (state->render_state->m_enable_diffuse_shading)
            {
                return RenderLightingWithoutShadowsSolid(state);
            }
        }
    }

    IRenderContext* RenderLighting(CoreState* state)
    {
        if (!state->render_state->m_enable_shadows || !state->batch_state->m_receive_shadows)
            //  shadow disabled
            return RenderLightingWithoutShadows(state);
        else
            //  shadows enabled
            return RenderLightingWithShadows(state);
    }

    IRenderContext* RenderSolidTextured(CoreState* state)
    {
        if (state->render_state->m_enable_diffuse_shading)
        {
            if (BindTexture(state))
                return IRenderContext::find(RenderPolicySet::SolidTextured2DArray);
            else
                return IRenderContext::find(RenderPolicySet::SolidTextured2D);
        }
        throw System::PunkException(L"Render not found");
    }

    IRenderContext* RenderSolidColored(CoreState* state)
    {
        if (state->render_state->m_enable_font_rendering)
        {
            if (BindTexture(state))
                //  text map retrieved as sampler2darray with layer
            ;
            else
                //  text map retrieved as sampler2d
                return IRenderContext::find(RenderPolicySet::TextSolidColor);
        }
        else if (state->render_state->m_enable_diffuse_shading)
        {
            if (state->render_state->m_enable_vertex_color)
                //  use color from vertex attributes
                return IRenderContext::find(RenderPolicySet::SolidVertexColor);
            else
                //	use color from uniform parameters
                return IRenderContext::find(RenderPolicySet::Solid3D);
        }
        throw System::PunkException(L"Render not found");
    }

    IRenderContext* RenderSolid(CoreState* state)
    {
        if (state->render_state->m_enable_texture)
            return RenderSolidTextured(state);
        else
            return RenderSolidColored(state);
    }

    IRenderContext* ChooseRender(CoreState* state)
    {
        if (state->render_state->m_render_depth)
            return RenderDepth(state);
        else if (state->render_state->m_enable_terrain)
            return RenderTerrain(state);
        else if (state->render_state->m_enable_lighting)
            return RenderLighting(state);
        else	//	NO LIGHTING
            return RenderSolid(state);
        return nullptr;
    }

	void RenderPass::OnePass(Renderable* renderable, CoreState* state)
    {
        TextureContext tc;
        IRenderContext* policy = ChooseRender(state);

        if (policy)
        {
       //     tc.Bind();
            policy->Begin();
            policy->BindParameters(*state);
            renderable->Bind(policy->GetRequiredAttributesSet());
            renderable->Render();
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
            OnePass(batch->m_renderable, batch->m_state);
		}
	}
}
PUNK_ENGINE_END
