#include <graphics/state/module.h>
#include <graphics/error/module.h>
#include <graphics/render/render_context/irender_context.h>
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

    IRenderContext* RenderDepth(CoreState* state)
    {
        if (state->render_state->m_enable_skinning)
        {
            return GetRenderContext(RenderPolicySet::DepthRenderSkinning);
        }
        else
        {
            return GetRenderContext(RenderPolicySet::DepthRender);
        }
    }

    IRenderContext* RenderTerrain(CoreState* state)
    {
        if (BindTexture(state))
            ;
        else
            return GetRenderContext(RenderPolicySet::Terrain);
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
                        return GetRenderContext(RenderPolicySet::BumpMappingTextureDiffuseSpecularSkinningShadowingSimple);
                    else
                        return GetRenderContext(RenderPolicySet::BumpMappingTextureDiffuseSpecularShadowingSimple);
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return GetRenderContext(RenderPolicySet::BumpMappingTextureDiffuseSkinningShadowingSimple);
                    else
                        return GetRenderContext(RenderPolicySet::BumpMappingTextureDiffuseShadowingSimple);
                }
            }
            else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
            {
                if (state->render_state->m_enable_specular_shading)
                {
                    if (state->render_state->m_enable_skinning)
                        return GetRenderContext(RenderPolicySet::LightPerFragmentTextureDiffuseSpecularSkinningShadowingSimple);
                    else
                        return GetRenderContext(RenderPolicySet::LightPerFragmentTextureDiffuseSpecularShadowingSimple);
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return GetRenderContext(RenderPolicySet::LightPerFragmentTextureDiffuseSkinningShadowingSimple);
                    else
                        return GetRenderContext(RenderPolicySet::LightPerFragmentTextureDiffuseShadowingSimple);
                }
            }
            else if (state->light_state->m_light_model == LightModel::PerVertexDiffuse)
            {
                if (state->render_state->m_enable_specular_shading)
                {
                    if (state->render_state->m_enable_skinning)
                        return GetRenderContext(RenderPolicySet::LightPerVertexTextureDiffuseSpecularSkinningShadowingSimple);
                    else
                        return GetRenderContext(RenderPolicySet::LightPerVertexTextureDiffuseSpecularShadowingSimple);
                }
                else
                {
                    if (state->render_state->m_enable_skinning)
                        return GetRenderContext(RenderPolicySet::LightPerVertexTextureDiffuseSkinningShadowingSimple);
                    else
                        return GetRenderContext(RenderPolicySet::LightPerVertexTextureDiffuseShadowingSimple);
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
                return GetRenderContext(RenderPolicySet::LightPerVertexDiffuseShadowingSimple);
            }
            else if (state->render_state->m_shadow_model == ShadowModel::ShadowMapCascade)
            {
                return GetRenderContext(RenderPolicySet::LightPerVertexDiffuseShadowingCascade);
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_shadow_model == ShadowModel::ShadowMapSimple)
            {
                return GetRenderContext(RenderPolicySet::LightPerFragmentDiffuseShadowingSimple);
            }
            else if (state->render_state->m_shadow_model == ShadowModel::ShadowMapCascade)
            {
                return GetRenderContext(RenderPolicySet::LightPerFragmentDiffuseShadowingCascade);
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
                    return GetRenderContext(RenderPolicySet::LightPerVertexTextureDiffuseSpecularSkinning);
                else
                    return GetRenderContext(RenderPolicySet::LightPerVertexTextureDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::LightPerVertexTextureDiffuseSkinning);
                else
                    return GetRenderContext(RenderPolicySet::LightPerVertexTextureDiffuse);
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::LightPerFragmentTextureDiffuseSpecularSkinning);
                else
                    return GetRenderContext(RenderPolicySet::LightPerFragmentTextureDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::LightPerFragmentTextureDiffuseSkinning);
                else
                    return GetRenderContext(RenderPolicySet::LightPerFragmentTextureDiffuse);
            }
        }
        else if (state->light_state->m_light_model == LightModel::BumpMappingDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::BumpMappingTextureDiffuseSpecularSkinning);
                else
                    return GetRenderContext(RenderPolicySet::BumpMappingTextureDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::BumpMappingTextureDiffuseSkinning);
                else
                    return GetRenderContext(RenderPolicySet::BumpMappingTextureDiffuse);
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
                    return GetRenderContext(RenderPolicySet::LightPerVertexDiffuseSpecularSkinning);
                else
                    return GetRenderContext(RenderPolicySet::LightPerVertexDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::LightPerVertexDiffuseSkinning);
                else
                    return GetRenderContext(RenderPolicySet::LightPerVertexDiffuse);
            }
        }
        else if (state->light_state->m_light_model == LightModel::PerFragmentDiffuse)
        {
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::LightPerFragmentDiffuseSpecularSkinning);
                else
                    return GetRenderContext(RenderPolicySet::LightPerFragmentDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::LightPerFragmentDiffuseSkinning);
                else
                    return GetRenderContext(RenderPolicySet::LightPerFragmentDiffuse);
            }
        }
        else if (state->light_state->m_light_model == LightModel::BumpMappingDiffuse)
        {
            BindNormalMap(state);
            if (state->render_state->m_enable_specular_shading)
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::BumpMappingDiffuseSpecularSkinning);
                else
                    return GetRenderContext(RenderPolicySet::BumpMappingDiffuseSpecular);
            }
            else
            {
                if (state->render_state->m_enable_skinning)
                    return GetRenderContext(RenderPolicySet::BumpMappingDiffuseSkinning);
                else
                    return GetRenderContext(RenderPolicySet::BumpMappingDiffuse);
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
                return GetRenderContext(RenderPolicySet::SolidTextured2DArray);
            else
                return GetRenderContext(RenderPolicySet::SolidTextured2D);
        }
        throw Error::GraphicsException(L"LowLevelRender not found");
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
                return GetRenderContext(RenderPolicySet::TextSolidColor);
        }
        else if (state->render_state->m_enable_diffuse_shading)
        {
            if (state->render_state->m_enable_vertex_color)
                //  use color from vertex attributes
                return GetRenderContext(RenderPolicySet::SolidVertexColor);
            else
                //	use color from uniform parameters
                return GetRenderContext(RenderPolicySet::Solid3D);
        }
        throw Error::GraphicsException(L"LowLevelRender not found");
    }

    IRenderContext* RenderSolid(CoreState* state)
    {
        if (state->render_state->m_enable_texture)
            return RenderSolidTextured(state);
        else
            return RenderSolidColored(state);
    }

    IRenderContext* SelectRenderContext(CoreState* state)
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
}
PUNK_ENGINE_END
