#include <graphics/render/render_context/irender_context.h>
#include <graphics/render/render_context/gl_render_context/module.h>
#include <graphics/shaders/gl_shaders/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    static IRenderContext* g_rc[(int)RenderPolicySet::Count];

    IRenderContext* GetRenderContext(RenderPolicySet value) {
        return g_rc[GetIndex(value)];
    }

    bool InitRenderContexts(IVideoDriver *driver) {
        return OpenGL::InitRenderContexts(driver);
    }

    void DestroyRenderContexts() {
        OpenGL::DestroyRenderContexts();
    }

    namespace OpenGL
    {            
        void DestroyRenderContexts() {
            for (int i = 0; i < (int)RenderPolicySet::Count; ++i) {
                delete g_rc[i];
                g_rc[i] = nullptr;
            }
        }

        void CreateRc(RenderPolicySet policy, Shader* vs, Shader* ps, Shader* gs) {
            DynamicRenderContext* rc = new DynamicRenderContext(policy);
            rc->SetShaders(vs, ps, gs);
            g_rc[GetIndex(policy)] = rc;
        }

        bool InitRenderContexts(IVideoDriver* driver) {

            CreateRc(RenderPolicySet::Solid3D, new VsSolid, new FsSolid, nullptr);
            CreateRc(RenderPolicySet::DepthRender, new VsDepth, new FsDepth, nullptr);
            CreateRc(RenderPolicySet::SolidVertexColor, new VsSolidVertexColor, new FsSolidVertexColor, nullptr);
            CreateRc(RenderPolicySet::SolidTextured2D, new VsTexture3D, new FsSolidTextured3D, nullptr);
            CreateRc(RenderPolicySet::LightPerVertexDiffuse, new VsPerVertexLightingDiffuse(), new FsPerVertexLightingDiffuse(), nullptr);
            CreateRc(RenderPolicySet::LightPerFragmentDiffuse, new VsPerFragmentLightingDiffuse, new FsPerFragmentLightingDiffuse, nullptr);
            CreateRc(RenderPolicySet::LightPerVertexTextureDiffuse, new VsPerVertexLightingTextureDiffuse, new FsPerVertexLightingTextureDiffuse, nullptr);
            CreateRc(RenderPolicySet::LightPerFragmentTextureDiffuse, new VsPerFragmentLightingTextureDiffuse, new FsPerFragmentLightingTextureDiffuse, nullptr);
            //CreateRc(RenderPolicySet::BumpMappingTextureDiffuse, new VsBumpMappingTextureDiffuse, new FsBumpMappingTextureDiffuse, nullptr);
            //CreateRc(RenderPolicySet::BumpMappingShadowingSingle, new VsBumpShadowMap, new FsBumpShadowMap, nullptr);
            CreateRc(RenderPolicySet::BumpMappingTextureDiffuseSkinning, new VsSkinningBump, new FsBumpMappingTextureDiffuse, nullptr);
            CreateRc(RenderPolicySet::DepthRenderSkinning, new VsSkinningDepth, new FsDepth, nullptr);
            CreateRc(RenderPolicySet::TextSolidColor, new VsTexture3D, new FsTextSolid, nullptr);
            CreateRc(RenderPolicySet::LightPerVertexTextureDiffuseShadowingSimple, new VsPerVertexLightingDiffuseShadowSimple, new FsPerVertexLightingDiffuseSimpleShadow, nullptr);
            CreateRc(RenderPolicySet::SolidTextured2DArray, new VsTexture3D, new FsSolidTextured2DArray, nullptr);
            CreateRc(RenderPolicySet::LightPerVertexDiffuseShadowingSimple, new VsPerVertexLightingDiffuseShadowSimple, new FsPerVertexLightingDiffuseSimpleShadow, nullptr);
            CreateRc(RenderPolicySet::LightPerFragmentDiffuseSpecular, new VsPerFragmentLightingDiffuseSpecular, new FsPerFragmentLightingDiffuseSpecular, nullptr);
            CreateRc(RenderPolicySet::LightPerFragmentTextureDiffuseSpecular, new VsPerFragmentLightingTextureDiffuseSpecular, new FsPerFragmentLightingTextureDiffuseSpecular, nullptr);
            CreateRc(RenderPolicySet::BumpMappingDiffuseSpecular, new VsBumpMappingDiffuseColorSpecular, new FsBumpMappingDiffuseColorSpecular, nullptr);
            CreateRc(RenderPolicySet::BumpMappingDiffuse, new VsBumpMappingDiffuseColor, new FsBumpMappingDiffuseColor, nullptr);
            CreateRc(RenderPolicySet::BumpMappingTextureDiffuseSpecular, new VsBumpMappingTextureDiffuseSpecular, new FsBumpMappingTextureDiffuseSpecular, nullptr);

            return true;
        }        
    }
}
PUNK_ENGINE_END
