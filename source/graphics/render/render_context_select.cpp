#include <graphics/state/module.h>
#include <graphics/error/module.h>
#include <graphics/render/irender_context.h>
#include <graphics/texture/module.h>
#include "render_context_select.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
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

	RenderContextType RenderDepth(CoreState* state)
    {
        if (state->render_state->m_enable_skinning)
        {
            return RenderContextType::DepthRenderSkinning;
        }
        else
        {
            return RenderContextType::DepthRender;
        }
    }

	RenderContextType RenderTerrain(CoreState* state)
    {
        /*if (BindTexture(state))
            ;
        else
            return RenderContextType::Terrain;*/
        return RenderContextType::NoRender;
    }

	RenderContextType RenderLightingWithShadowsSimpleTextured(CoreState* state)
    {
        BindTexture(state);
        if (state->render_state->m_enable_diffuse_shading)
        {
            if (state->light_state->m_light_model == LightModel::BumpMappingDiffuse)
            {
                if (state->render_state->m_enable_specular_shading)
                {
                    if (state->render_state->m_enable_skinning)
                        return RenderContextType::BumpMappingTextureDiffuseSpecularSkinningShadowingSimple;
                    else
                        return RenderContextType::BumpMappingTextureDiffuseSpecularShadowingSimple;
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return RenderContextType::BumpMappingTextureDiffuseSkinningShadowingSimple;
                    else
                        return RenderContextType::BumpMappingTextureDiffuseShadowingSimple;
                }
            }
            else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
            {
                if (state->render_state->m_enable_specular_shading)
                {
                    if (state->render_state->m_enable_skinning)
                        return RenderContextType::LightPerFragmentTextureDiffuseSpecularSkinningShadowingSimple;
                    else
                        return RenderContextType::LightPerFragmentTextureDiffuseSpecularShadowingSimple;
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return RenderContextType::LightPerFragmentTextureDiffuseSkinningShadowingSimple;
                    else
                        return RenderContextType::LightPerFragmentTextureDiffuseShadowingSimple;
                }
            }
            else if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
            {
                if (state->render_state->m_enable_specular_shading)
                {
                    if (state->render_state->m_enable_skinning)
                        return RenderContextType::LightPerVertexTextureDiffuseSpecularSkinningShadowingSimple;
                    else
                        return RenderContextType::LightPerVertexTextureDiffuseSpecularShadowingSimple;
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return RenderContextType::LightPerVertexTextureDiffuseSkinningShadowingSimple;
                    else
                        return RenderContextType::LightPerVertexTextureDiffuseShadowingSimple;
                }
            }
        }
		return RenderContextType::NoRender;
    }

	RenderContextType RenderLightingWithShadowsSimpleSolid(CoreState* state)
    {
        if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
        {
            if (state->render_state->m_shadow_model == ShadowModel::ShadowMapSimple)
            {
                return RenderContextType::LightPerVertexDiffuseShadowingSimple;
            }
            else if (state->render_state->m_shadow_model == ShadowModel::ShadowMapCascade)
            {
                return RenderContextType::LightPerVertexDiffuseShadowingCascade;
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_shadow_model == ShadowModel::ShadowMapSimple)
            {
                return RenderContextType::LightPerFragmentDiffuseShadowingSimple;
            }
            else if (state->render_state->m_shadow_model == ShadowModel::ShadowMapCascade)
            {
                return RenderContextType::LightPerFragmentDiffuseShadowingCascade;
            }
        }
		return RenderContextType::NoRender;
    }

	RenderContextType RenderLightingWithShadowsCascadeTextured(CoreState* state)
    {
		return RenderContextType::NoRender;
    }

	RenderContextType RenderLightingWithShadowsCascadeSolid(CoreState* state)
    {
		return RenderContextType::NoRender;
    }

	RenderContextType RenderLightingWithShadows(CoreState* state)
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
		return RenderContextType::NoRender;
    }

	RenderContextType RenderLightingWithoutShadowsTextured(CoreState* state)
    {
        BindTexture(state);
        if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::LightPerVertexTextureDiffuseSpecularSkinning;
                else
                    return RenderContextType::LightPerVertexTextureDiffuseSpecular;
            }
            else
            {
				if (state->render_state->m_enable_skinning)
					return RenderContextType::LightPerVertexTextureDiffuseSkinning;
                else
                    return RenderContextType::LightPerVertexTextureDiffuse;
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::LightPerFragmentTextureDiffuseSpecularSkinning;
                else
                    return RenderContextType::LightPerFragmentTextureDiffuseSpecular;
            }
            else
            {
				if (state->render_state->m_enable_skinning)
					return RenderContextType::LightPerFragmentTextureDiffuseSkinning;
                else
                    return RenderContextType::LightPerFragmentTextureDiffuse;
            }
        }
        else if (state->light_state->m_light_model == LightModel::BumpMappingDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::BumpMappingTextureDiffuseSpecularSkinning;
                else
                    return RenderContextType::BumpMappingTextureDiffuseSpecular;
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::BumpMappingTextureDiffuseSkinning;
                else
                    return RenderContextType::BumpMappingTextureDiffuse;
            }
        }
		return RenderContextType::NoRender;
    }

	RenderContextType RenderLightingWithoutShadowsSolid(CoreState* state)
    {
        if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::LightPerVertexDiffuseSpecularSkinning;
                else
                    return RenderContextType::LightPerVertexDiffuseSpecular;
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::LightPerVertexDiffuseSkinning;
                else
                    return RenderContextType::LightPerVertexDiffuse;
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::LightPerFragmentDiffuseSpecularSkinning;
                else
                    return RenderContextType::LightPerFragmentDiffuseSpecular;
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::LightPerFragmentDiffuseSkinning;
                else
                    return RenderContextType::LightPerFragmentDiffuse;
            }
        }
        else if (state->light_state->m_light_model == LightModel::BumpMappingDiffuse)
        {
            BindNormalMap(state);
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::BumpMappingDiffuseSpecularSkinning;
                else
                    return RenderContextType::BumpMappingDiffuseSpecular;
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return RenderContextType::BumpMappingDiffuseSkinning;
                else
                    return RenderContextType::BumpMappingDiffuse;
            }
        }
		return RenderContextType::NoRender;
    }

	RenderContextType RenderLightingWithoutShadows(CoreState *state)
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
		return RenderContextType::NoRender;
    }

	RenderContextType RenderLighting(CoreState* state)
    {
        if (!state->render_state->m_enable_shadows || !state->batch_state->m_receive_shadows)
            //  shadow disabled
            return RenderLightingWithoutShadows(state);
        else
            //  shadows enabled
            return RenderLightingWithShadows(state);
    }

	RenderContextType RenderSolidTextured(CoreState* state)
    {
        if (state->render_state->m_enable_diffuse_shading)
        {
			if (BindTexture(state))
				return RenderContextType::NoLightSolidColorTextured;
			else
				return RenderContextType::NoLightSolidColor;
        }
		return RenderContextType::NoRender;
    }

	RenderContextType RenderSolidColored(CoreState* state)
    {
        if (state->render_state->m_enable_font_rendering)
        {
            if (BindTexture(state))
                //  text map retrieved as sampler2darray with layer
                ;
            else
                //  text map retrieved as sampler2d
                return RenderContextType::TextSolidColor;
        }
        else if (state->render_state->m_enable_diffuse_shading)
        {
            if (state->render_state->m_enable_vertex_color)
                //  use color from vertex attributes
                return RenderContextType::NoLightVertexColor;
            else
                //	use color from uniform parameters
                return RenderContextType::NoLightSolidColor;
        }
		return RenderContextType::NoRender;
    }

	RenderContextType RenderSolid(CoreState* state)
    {
        if (state->render_state->m_enable_texture)
            return RenderSolidTextured(state);
        else
            return RenderSolidColored(state);
    }

	RenderContextType SelectRenderContext(CoreState* state)
    {
        if (state->render_state->m_render_depth)
            return RenderDepth(state);
        else if (state->render_state->m_enable_terrain)
            return RenderTerrain(state);
        else if (state->render_state->m_enable_lighting)
            return RenderLighting(state);
        else	//	NO LIGHTING
            return RenderSolid(state);
		return RenderContextType::NoRender;
    }
}
PUNK_ENGINE_END
