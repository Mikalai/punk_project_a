#include <graphics/error/module.h>
#include "irender_context.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    IRenderContext::IRenderContext()
        : m_was_modified(false)
        , m_vertex_attributes(VertexComponent::NoComponent::Value())
    {}

    IRenderContext::~IRenderContext()
    {
    }

    extern PUNK_ENGINE_API const Core::String RenderPolicySetToString(RenderPolicySet policy) {
        switch (policy) {
        case RenderPolicySet::Solid3D:
            return Core::String(L"Solid3D");
        case RenderPolicySet::SolidTextured2D:
            return Core::String(L"SolidTextured2D");
        case RenderPolicySet::SolidTextured2DArray:
            return Core::String(L"SolidTextured2DArray");
        case RenderPolicySet::GUI:
            return Core::String(L"GUI");
        case RenderPolicySet::Terrain:
            return Core::String(L"Terrain");
        case RenderPolicySet::Painter:
            return Core::String(L"Painter");
        case RenderPolicySet::SolidVertexColor:
            return Core::String(L"SolidVertexColor");
        case RenderPolicySet::BumpMappingDiffuse:
            return Core::String(L"BumpMappingDiffuse");
        case RenderPolicySet::BumpMappingDiffuseShadowingSimple:
            return Core::String(L"BumpMappingDiffuseShadowingSimple");
        case RenderPolicySet::BumpMappingDiffuseShadowingCascade:
            return Core::String(L"BumpMappingDiffuseShadowingCascade");
        case RenderPolicySet::BumpMappingDiffuseSkinning:
            return Core::String(L"BumpMappingDiffuseSkinning");
        case RenderPolicySet::BumpMappingDiffuseSkinningShadowingSimple:
            return Core::String(L"BumpMappingDiffuseSkinningShadowingSimple");
        case RenderPolicySet::BumpMappingDiffuseSkinningShadowingCascade:
            return Core::String(L"BumpMappingDiffuseSkinningShadowingCascade");
        case RenderPolicySet::BumpMappingDiffuseSpecular:
            return Core::String(L"BumpMappingDiffuseSpecular");
        case RenderPolicySet::BumpMappingDiffuseSpecularShadowingSimple:
            return Core::String(L"BumpMappingDiffuseSpecularShadowingSimple");
        case RenderPolicySet::BumpMappingDiffuseSpecularShadowingCascade:
            return Core::String(L"BumpMappingDiffuseSpecularShadowingCascade");
        case RenderPolicySet::BumpMappingDiffuseSpecularSkinning:
            return Core::String(L"BumpMappingDiffuseSpecularSkinning");
        case RenderPolicySet::BumpMappingDiffuseSpecularSkinningShadowingSimple:
            return Core::String(L"BumpMappingDiffuseSpecularSkinningShadowingSimple");
        case RenderPolicySet::BumpMappingDiffuseSpecularSkinningShadowingCascade:
            return Core::String(L"BumpMappingDiffuseSpecularSkinningShadowingCascade");
        case RenderPolicySet::BumpMappingTextureDiffuse:
            return Core::String(L"BumpMappingTextureDiffuse");
        case RenderPolicySet::BumpMappingTextureDiffuseShadowingSimple:
            return Core::String(L"BumpMappingTextureDiffuseShadowingSimple");
        case RenderPolicySet::BumpMappingTextureDiffuseShadowingCascade:
            return Core::String(L"BumpMappingTextureDiffuseShadowingCascade");
        case RenderPolicySet::BumpMappingTextureDiffuseSkinning:
            return Core::String(L"BumpMappingTextureDiffuseSkinning");
        case RenderPolicySet::BumpMappingTextureDiffuseSkinningShadowingSimple:
            return Core::String(L"BumpMappingTextureDiffuseSkinningShadowingSimple");
        case RenderPolicySet::BumpMappingTextureDiffuseSkinningShadowingCascade:
            return Core::String(L"BumpMappingTextureDiffuseSkinningShadowingCascade");
        case RenderPolicySet::BumpMappingTextureDiffuseSpecular:
            return Core::String(L"BumpMappingTextureDiffuseSpecular");
        case RenderPolicySet::BumpMappingTextureDiffuseSpecularShadowingSimple:
            return Core::String(L"BumpMappingTextureDiffuseSpecularShadowingSimple");
        case RenderPolicySet::BumpMappingTextureDiffuseSpecularShadowingCascade:
            return Core::String(L"BumpMappingTextureDiffuseSpecularShadowingCascade");
        case RenderPolicySet::BumpMappingTextureDiffuseSpecularSkinning:
            return Core::String(L"BumpMappingTextureDiffuseSpecularSkinning");
        case RenderPolicySet::BumpMappingTextureDiffuseSpecularSkinningShadowingSimple:
            return Core::String(L"BumpMappingTextureDiffuseSpecularSkinningShadowingSimple");
        case RenderPolicySet::BumpMappingTextureDiffuseSpecularSkinningShadowingCascade:
            return Core::String(L"BumpMappingTextureDiffuseSpecularSkinningShadowingCascade");
        case RenderPolicySet::LightPerFragmentDiffuse:
            return Core::String(L"LightPerFragmentDiffuse");
        case RenderPolicySet::LightPerFragmentDiffuseShadowingSimple:
            return Core::String(L"LightPerFragmentDiffuseShadowingSimple");
        case RenderPolicySet::LightPerFragmentDiffuseShadowingCascade:
            return Core::String(L"LightPerFragmentDiffuseShadowingCascade");
        case RenderPolicySet::LightPerFragmentDiffuseSkinning:
            return Core::String(L"LightPerFragmentDiffuseSkinning");
        case RenderPolicySet::LightPerFragmentDiffuseSkinningShadowingSimple:
            return Core::String(L"LightPerFragmentDiffuseSkinningShadowingSimple");
        case RenderPolicySet::LightPerFragmentDiffuseSkinningShadowingCascade:
            return Core::String(L"LightPerFragmentDiffuseSkinningShadowingCascade");
        case RenderPolicySet::LightPerFragmentDiffuseSpecular:
            return Core::String(L"LightPerFragmentDiffuseSpecular");
        case RenderPolicySet::LightPerFragmentDiffuseSpecularShadowingSimple:
            return Core::String(L"LightPerFragmentDiffuseSpecularShadowingSimple");
        case RenderPolicySet::LightPerFragmentDiffuseSpecularShadowingCascade:
            return Core::String(L"LightPerFragmentDiffuseSpecularShadowingCascade");
        case RenderPolicySet::LightPerFragmentDiffuseSpecularSkinning:
            return Core::String(L"LightPerFragmentDiffuseSpecularSkinning");
        case RenderPolicySet::LightPerFragmentDiffuseSpecularSkinningShadowingSimple:
            return Core::String(L"LightPerFragmentDiffuseSpecularSkinningShadowingSimple");
        case RenderPolicySet::LightPerFragmentDiffuseSpecularSkinningShadowingCascade:
            return Core::String(L"LightPerFragmentDiffuseSpecularSkinningShadowingCascade");
        case RenderPolicySet::LightPerFragmentTextureDiffuse:
            return Core::String(L"LightPerFragmentTextureDiffuse");
        case RenderPolicySet::LightPerFragmentTextureDiffuseShadowingSimple:
            return Core::String(L"LightPerFragmentTextureDiffuseShadowingSimple");
        case RenderPolicySet::LightPerFragmentTextureDiffuseShadowingCascade:
            return Core::String(L"LightPerFragmentTextureDiffuseShadowingCascade");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSkinning:
            return Core::String(L"LightPerFragmentTextureDiffuseSkinning");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSkinningShadowingSimple:
            return Core::String(L"LightPerFragmentTextureDiffuseSkinningShadowingSimple");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSkinningShadowingCascade:
            return Core::String(L"LightPerFragmentTextureDiffuseSkinningShadowingCascade");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSpecular:
            return Core::String(L"LightPerFragmentTextureDiffuseSpecular");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSpecularShadowingSimple:
            return Core::String(L"LightPerFragmentTextureDiffuseSpecularShadowingSimple");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSpecularShadowingCascade:
            return Core::String(L"LightPerFragmentTextureDiffuseSpecularShadowingCascade");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSpecularSkinning:
            return Core::String(L"LightPerFragmentTextureDiffuseSpecularSkinning");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSpecularSkinningShadowingSimple:
            return Core::String(L"LightPerFragmentTextureDiffuseSpecularSkinningShadowingSimple");
        case RenderPolicySet::LightPerFragmentTextureDiffuseSpecularSkinningShadowingCascade:
            return Core::String(L"LightPerFragmentTextureDiffuseSpecularSkinningShadowingCascade");
        case RenderPolicySet::LightPerVertexDiffuse:
            return Core::String(L"LightPerVertexDiffuse");
        case RenderPolicySet::LightPerVertexDiffuseShadowingCascade:
            return Core::String(L"LightPerVertexDiffuseShadowingCascade");
        case RenderPolicySet::LightPerVertexDiffuseShadowingSimple:
            return Core::String(L"LightPerVertexDiffuseShadowingSimple");
        case RenderPolicySet::LightPerVertexDiffuseSkinning:
            return Core::String(L"LightPerVertexDiffuseSkinning");
        case RenderPolicySet::LightPerVertexDiffuseSkinningShadowingCascade:
            return Core::String(L"LightPerVertexDiffuseSkinningShadowingCascade");
        case RenderPolicySet::LightPerVertexDiffuseSkinningShadowingSimple:
            return Core::String(L"LightPerVertexDiffuseSkinningShadowingSimple");
        case RenderPolicySet::LightPerVertexDiffuseSpecular:
            return Core::String(L"LightPerVertexDiffuseSpecular");
        case RenderPolicySet::LightPerVertexDiffuseSpecularShadowingSimple:
            return Core::String(L"LightPerVertexDiffuseSpecularShadowingSimple");
        case RenderPolicySet::LightPerVertexDiffuseSpecularShadowingCascade:
            return Core::String(L"LightPerVertexDiffuseSpecularShadowingCascade");
        case RenderPolicySet::LightPerVertexDiffuseSpecularSkinning:
            return Core::String(L"LightPerVertexDiffuseSpecularSkinning");
        case RenderPolicySet::LightPerVertexDiffuseSpecularSkinningShadowingSimple:
            return Core::String(L"LightPerVertexDiffuseSpecularSkinningShadowingSimple");
        case RenderPolicySet::LightPerVertexDiffuseSpecularSkinningShadowingCascade:
            return Core::String(L"LightPerVertexDiffuseSpecularSkinningShadowingCascade");
        case RenderPolicySet::LightPerVertexTextureDiffuse:
            return Core::String(L"LightPerVertexTextureDiffuse");
        case RenderPolicySet::LightPerVertexTextureDiffuseShadowingSimple:
            return Core::String(L"LightPerVertexTextureDiffuseShadowingSimple");
        case RenderPolicySet::LightPerVertexTextureDiffuseShadowingCascade:
            return Core::String(L"LightPerVertexTextureDiffuseShadowingCascade");
        case RenderPolicySet::LightPerVertexTextureDiffuseSkinning:
            return Core::String(L"LightPerVertexTextureDiffuseSkinning");
        case RenderPolicySet::LightPerVertexTextureDiffuseSkinningShadowingSimple:
            return Core::String(L"LightPerVertexTextureDiffuseSkinningShadowingSimple");
        case RenderPolicySet::LightPerVertexTextureDiffuseSkinningShadowingCascade:
            return Core::String(L"LightPerVertexTextureDiffuseSkinningShadowingCascade");
        case RenderPolicySet::LightPerVertexTextureDiffuseSpecular:
            return Core::String(L"LightPerVertexTextureDiffuseSpecular");
        case RenderPolicySet::LightPerVertexTextureDiffuseSpecularShadowingSimple:
            return Core::String(L"LightPerVertexTextureDiffuseSpecularShadowingSimple");
        case RenderPolicySet::LightPerVertexTextureDiffuseSpecularShadowingCascade:
            return Core::String(L"LightPerVertexTextureDiffuseSpecularShadowingCascade");
        case RenderPolicySet::LightPerVertexTextureDiffuseSpecularSkinning:
            return Core::String(L"LightPerVertexTextureDiffuseSpecularSkinning");
        case RenderPolicySet::LightPerVertexTextureDiffuseSpecularSkinningShadowingSimple:
            return Core::String(L"LightPerVertexTextureDiffuseSpecularSkinningShadowingSimple");
        case RenderPolicySet::LightPerVertexTextureDiffuseSpecularSkinningShadowingCascade:
            return Core::String(L"LightPerVertexTextureDiffuseSpecularSkinningShadowingCascade");
        case RenderPolicySet::TextSolidColor:
            return Core::String(L"TextSolidColor");
        case RenderPolicySet::DepthRender:
            return Core::String(L"DepthRender");
        case RenderPolicySet::DepthRenderSkinning:
            return Core::String(L"DepthRenderSkinning");
		default:
			throw Error::GraphicsException("Unknown render context");
        };
    }
}
PUNK_ENGINE_END
