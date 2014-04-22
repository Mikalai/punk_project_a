#ifndef _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT
#define _H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT

#include <config.h>
#include <graphics/state/module.h>
#include <graphics/primitives/module.h>
#include <system/aop/aop.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	enum class RenderPolicySet {
        Solid3D,
        SolidTextured2D,
        SolidTextured2DArray,
		GUI,
		Terrain,
        Painter,
        SolidVertexColor,

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
        End
	};

    extern PUNK_ENGINE_API const Core::String RenderPolicySetToString(RenderPolicySet policy);

    inline int GetIndex(RenderPolicySet policy) {
        return (int)policy;
    }

    class PUNK_ENGINE_API IRenderContext : public System::Aspect<IRenderContext*, RenderPolicySet>
	{
	public:
        IRenderContext();
        virtual void InitUniforms() = 0;
        virtual void BindParameters(const CoreState& params) = 0;
        virtual int64_t GetRequiredAttributesSet() const = 0;
        virtual void Begin() = 0;
        virtual void End() = 0;
        virtual void Init() = 0;
        virtual RenderPolicySet GetPolicy() = 0;
        virtual ~IRenderContext();
	protected:
		bool m_was_modified;
		int64_t  m_vertex_attributes;
	};

    IRenderContext* GetRenderContext(RenderPolicySet value);
    bool InitRenderContexts(IVideoDriver* driver);
    void DestroyRenderContexts();
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_ABSTRACT_RENDER_CONTEXT
