#ifndef _H_RENDER_CONTEXT_TYPE
#define _H_RENDER_CONTEXT_TYPE

#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics {

	enum class RenderContextType : std::int32_t {
		NoRender = -1,

		NoLightSolidColor,
		NoLightSolidColorTextured,
		NoLightSolidColorSkinning,
		NoLightSolidColorTexturedSkinning,

		NoLightVertexColor,
		NoLightVertexColorTextured,
		NoLightVertexColorSkinning,
		NoLightVertexColorTexturedSkinning,

		BumpMappingDiffuse,
		BumpMappingDiffuseShadowingSimple,
		BumpMappingDiffuseShadowingCascade,

		BumpMappingDiffuseSkinning,
		BumpMappingDiffuseSkinningShadowingSimple,
		BumpMappingDiffuseSkinningShadowingCascade,

		BumpMappingDiffuseSpecular,
		BumpMappingDiffuseSpecularShadowingSimple,
		BumpMappingDiffuseSpecularShadowingCascade,

		BumpMappingDiffuseSpecularSkinning,
		BumpMappingDiffuseSpecularSkinningShadowingSimple,
		BumpMappingDiffuseSpecularSkinningShadowingCascade,

		BumpMappingTextureDiffuse,
		BumpMappingTextureDiffuseShadowingSimple,
		BumpMappingTextureDiffuseShadowingCascade,

		BumpMappingTextureDiffuseSkinning,
		BumpMappingTextureDiffuseSkinningShadowingSimple,
		BumpMappingTextureDiffuseSkinningShadowingCascade,

		BumpMappingTextureDiffuseSpecular,
		BumpMappingTextureDiffuseSpecularShadowingSimple,
		BumpMappingTextureDiffuseSpecularShadowingCascade,

		BumpMappingTextureDiffuseSpecularSkinning,
		BumpMappingTextureDiffuseSpecularSkinningShadowingSimple,
		BumpMappingTextureDiffuseSpecularSkinningShadowingCascade,

		LightPerFragmentDiffuse,
		LightPerFragmentDiffuseShadowingSimple,
		LightPerFragmentDiffuseShadowingCascade,

		LightPerFragmentDiffuseSkinning,
		LightPerFragmentDiffuseSkinningShadowingSimple,
		LightPerFragmentDiffuseSkinningShadowingCascade,

		LightPerFragmentDiffuseSpecular,
		LightPerFragmentDiffuseSpecularShadowingSimple,
		LightPerFragmentDiffuseSpecularShadowingCascade,

		LightPerFragmentDiffuseSpecularSkinning,
		LightPerFragmentDiffuseSpecularSkinningShadowingSimple,
		LightPerFragmentDiffuseSpecularSkinningShadowingCascade,

		LightPerFragmentTextureDiffuse,
		LightPerFragmentTextureDiffuseShadowingSimple,
		LightPerFragmentTextureDiffuseShadowingCascade,

		LightPerFragmentTextureDiffuseSkinning,
		LightPerFragmentTextureDiffuseSkinningShadowingSimple,
		LightPerFragmentTextureDiffuseSkinningShadowingCascade,

		LightPerFragmentTextureDiffuseSpecular,
		LightPerFragmentTextureDiffuseSpecularShadowingSimple,
		LightPerFragmentTextureDiffuseSpecularShadowingCascade,

		LightPerFragmentTextureDiffuseSpecularSkinning,
		LightPerFragmentTextureDiffuseSpecularSkinningShadowingSimple,
		LightPerFragmentTextureDiffuseSpecularSkinningShadowingCascade,

		LightPerVertexDiffuse,
		LightPerVertexDiffuseShadowingCascade,
		LightPerVertexDiffuseShadowingSimple,

		LightPerVertexDiffuseSkinning,
		LightPerVertexDiffuseSkinningShadowingCascade,
		LightPerVertexDiffuseSkinningShadowingSimple,

		LightPerVertexDiffuseSpecular,
		LightPerVertexDiffuseSpecularShadowingSimple,
		LightPerVertexDiffuseSpecularShadowingCascade,

		LightPerVertexDiffuseSpecularSkinning,
		LightPerVertexDiffuseSpecularSkinningShadowingSimple,
		LightPerVertexDiffuseSpecularSkinningShadowingCascade,

		LightPerVertexTextureDiffuse,
		LightPerVertexTextureDiffuseShadowingSimple,
		LightPerVertexTextureDiffuseShadowingCascade,

		LightPerVertexTextureDiffuseSkinning,
		LightPerVertexTextureDiffuseSkinningShadowingSimple,
		LightPerVertexTextureDiffuseSkinningShadowingCascade,

		LightPerVertexTextureDiffuseSpecular,
		LightPerVertexTextureDiffuseSpecularShadowingSimple,
		LightPerVertexTextureDiffuseSpecularShadowingCascade,

		LightPerVertexTextureDiffuseSpecularSkinning,
		LightPerVertexTextureDiffuseSpecularSkinningShadowingSimple,
		LightPerVertexTextureDiffuseSpecularSkinningShadowingCascade,

		TextSolidColor,
		DepthRender,
		DepthRenderSkinning,
		TotalCount
	};

	PUNK_ENGINE_API const Core::String RenderPolicySetToString(RenderContextType policy);

	inline int GetIndex(RenderContextType policy) {
		return (int)policy;
	}
}
PUNK_ENGINE_END

#endif	//	_H_RENDER_CONTEXT_TYPE