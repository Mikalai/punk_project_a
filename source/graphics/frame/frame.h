#ifndef _H_PUNK_COMMON_RENDER_FRAME
#define _H_PUNK_COMMON_RENDER_FRAME

#include <config.h>
#include <graphics/state/module.h>
#include <core/poolable.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include "iframe.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class IVideoDriver;
    class ITexture2D;
    class ITextSurface;
    class IRenderable;
    class IFrameBuffer;
    class ILowLevelRender;

	class Batch;    

    class PUNK_ENGINE_LOCAL Frame : public IFrame//, public Core::Poolable<Frame>
	{
	public:

        Frame();
        virtual ~Frame();

		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

        ILowLevelRender* GetRender() override;
		void SetRender(ILowLevelRender* render) override;
        void Submit(Core::Pointer<IRenderable> value) override;
        void SetClipSpace(const Math::ClipSpace& value) override;
        const Math::ClipSpace& GetClipSpace() const override;
        void SetLineWidth(float value) override;
        void SetPointSize(float value) override;
        void SetBoundingSphere(const Math::BoundingSphere& value) override;

        //  MATRIX
        void SetBoneMatrix(int bone_index, const Math::mat4& value) override;
        const Math::mat4& GetBoneMatrix(int bone_index) const override;
        void SetTextureMatrix(const Math::mat4& value) override;
        void SetLocalMatrix(const Math::mat4& value) override;
        void SetWorldMatrix(const Math::mat4& value) override;
        void SetViewMatrix(const Math::mat4& value) override;
        void SetProjectionMatrix(const Math::mat4& value) override;
        void MultWorldMatrix(const Math::mat4& value) override;
        const Math::mat4& GetWorldMatrix() const override;
        const Math::mat4& GetLocalMatrix() const override;
        const Math::mat4& GetViewMatrix() const override;
        const Math::mat4& GetProjectionMatrix() const override;
		void SetArmatureMatrix(const Math::mat4& value) override;
		const Math::mat4& GetArmatureMatrix() const override;
		void SetOffsetMatrix(const Math::mat4& value) override;
		const Math::mat4& GetOffsetMatrix() const override;
		const Math::mat4& GetLastLocalMatrix() const override;

        //  COLORS
        void SetDiffuseColor(const Math::vec4& value) override;
        void SetDiffuseColor(float r, float g, float b, float a) override;
        void SetTextColor(const Math::vec4& value) override;
        void SetTextColor(float r, float g, float b, float a) override;
        void SetSpecularColor(const Math::vec4& value) override;
        const Math::vec4& GetSpecularColor() const override;
        void SetSpecularFactor(float value) override;
        void SetAmbientColor(float value) override;
        const Math::vec4& GetDiffuseColor() const override;

        //  MAPS
        void SetSpecularMap(ITexture2D* value, int slot) override;
        void SetBumpMap(ITexture2D* value, int slot) override;
        void SetDiffuseMap(int index, ITexture2D* value, int slot) override;
        void SetHeightMap(ITexture2D* value, int slot) override;
        void SetNormalMap(ITexture2D* value, int slot) override;
        void SetTextMap(ITexture2D* value, int slot) override;
        void SetFontMap(ITexture2D* value, int slot) override;
        const ITexture2D* GetDiffuseMap(int index) const override;
        const ITexture2D* GetSpecularMap() const override;
        const ITexture2D* GetBumpMap() const override;
		
        void CastShadows(bool value) override;
        void ReceiveShadow(bool value) override;
        void EndRendering() override;

        void EnableBlending(bool value) override;
        void EnableDepthTest(bool value) override;
        void EnableDiffuseShading(bool value) override;
        void EnableSpecularShading(bool value) override;
        //void EnableBumpMapping(bool value) override;
        void EnableSkinning(bool value) override;
		bool IsEnabledSkinning() const override;
        void EnableWireframe(bool value) override;
        void EnableTerrainRendering(bool value) override;
        void EnableLighting(bool value) override;
        bool IsLightingEnabled() const override;
        void EnableShadows(bool value) override;
        void EnableTexturing(bool value) override;
        void EnableFontRendering(bool value) override;
        void EnableBoundBoxRendering(bool value) override;
        void EnableDepthRendering(bool value) override;
        bool IsEnabledBoundingBoxRendering() const override;
        void EnableBoundingSphereRendering(bool value) override;
        bool IsEnabledBoundingSphereRendering() const override;
        void EnableNaviMeshRendering(bool value) override;
        bool IsEnabledNaviMeshRendering() override;

        //  added on 01.05.2013		
        void SetClearColor(const Math::vec4& value) override;
        void SetClearColor(float r, float g, float b, float a) override;
        void SetClearDepth(float value) override;

        void SetShadowModel(ShadowModel value) override;
        void SetShadowMapSize(const Math::ivec2& value) override;
        void SetShadowMapSize(int width, int height) override;
        void SetTexture2DArray(ITexture2DArray* value, int slot) override;
        //  index in current texture 2d array
        void SetShadowMapIndex(int shadow_map, int index) override;
        void SetDiffuseMapIndex(int diffuse_map, int index) override;
        void SetNormalMapIndex(int index) override;
        void SetShadowMaps(ITexture2DArray* value) override;


        const Math::vec4 GetClearColor() const override;

        //void Clear(bool color, bool depth, bool stencil) override;

        //  added on 02.05.2013
        void EnablePerVertexColor(bool value) override;

        void SetLightModel(LightModel value) override;
        LightParameters& Light(int slot) override;

        void DrawLine(const Math::vec3& start, const Math::vec3& end) override;
        void DrawLine(float x1, float y1, float x2, float y2) override;
        void DrawPoint(float x, float y) override;
        void DrawPoint(const Math::vec3& v) override;
        void DrawPoint(float x, float y, float z) override;
        void DrawCircleXY(float x, float y, float z, float r) override;
        //void DrawCircleXY(const Math::vec3& c, float r) override;
        void DrawQuad(float x, float y, float width, float height) override;
        void DrawQuad(const Math::Rectangle& rect) override;
        void DrawText2D(float x, float y, const Core::String& value) override;
//        void DrawText2D(float x, float y, float width, float height, const Core::String& value) override;
//        void DrawText2D(const Math::vec2& pos, const Core::String& value) override;
        void DrawText2D(const Math::vec2& pos, const Math::vec2& size, const Core::String& value) override;
//        void DrawText3D(float x, float y, float z, const Core::String& value) override;
//        void DrawText3D(const Math::vec3& pos, const Core::String& value) override;
        void DrawAxis(float scale = 10) override;

        void SetBlendColor(const Math::vec4& value) override;
        void SetBlendColor(float r, float g, float b, float a) override;
        void SetBlendFunc(BlendFunction src, BlendFunction dst) override;

        FogDescription& Fog() override;
        const FogDescription& Fog() const override;

        void PushAllState() override;
        void PopAllState() override;

        void PushViewState() override;
        void PopViewState() override;

        void PushLightState() override;
        void PopLightState() override;

        void PushRenderState() override;
        void PopRenderState() override;

        void PushBatchState() override;
        void PopBatchState() override;

        void PushTextureState() override;
        void PopTextureState() override;

        IVideoDriver* GetVideoDriver() const override;
		
		IRenderableBuilder* GetRenderableBuilder() override;

        const Math::vec2 FindZRange(const Math::mat4& view) const override;

	private:

		CoreState* Top();
		const CoreState* Top() const;

    private:
		//	next should be delete in destructor
		std::stack<CoreState*> m_state;

        //	next should not be deleted in destructor        
		ILowLevelRender* m_render{ nullptr };
        std::vector<ITextSurface*> m_texts;
		ITexture2DArray* m_shadow_maps{ nullptr };
		Core::Pointer<IRenderableBuilder> m_builder{ nullptr, Core::DestroyObject };

		Frame(const Frame&) = delete;
		Frame& operator = (const Frame&) = delete;

		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_COMMON_RENDER_FRAME
