#ifndef _H_PUNK_COMMON_RENDER_FRAME
#define _H_PUNK_COMMON_RENDER_FRAME

#include <config.h>
#include <graphics/state/module.h>
#include <core/poolable.h>

PUNK_ENGINE_BEGIN
namespace Math {
	class mat4;
	class vec4;
}

namespace Graphics
{
    class IVideoDriver;
    class ITexture2D;
    class ITextSurface;
    class IRenderable;
    class IFrameBuffer;
	class Batch;    

    class PUNK_ENGINE_API Frame : public Core::Poolable<Frame>
	{
	public:
		
		~Frame();

		void BeginRendering();
        //void BeginRendering(ITexture2D* color_buffer, ITexture2D* depth_buffer);
        void BeginRendering(IFrameBuffer* target);
        void Submit(IRenderable* value, bool destroy = false);

		void SetClipSpace(const Math::ClipSpace& value);		
        const Math::ClipSpace& GetClipSpace() const;
		void SetLineWidth(float value);
		void SetPointSize(float value);		
        void SetBoundingSphere(const Math::BoundingSphere& value);

        //  MATRIX
        void SetBoneMatrix(int bone_index, const Math::mat4& value);
        const Math::mat4& GetBoneMatrix(int bone_index) const;
        void SetTextureMatrix(const Math::mat4& value);
        void SetLocalMatrix(const Math::mat4& value);
        void SetWorldMatrix(const Math::mat4& value);
        void SetViewMatrix(const Math::mat4& value);
        void SetProjectionMatrix(const Math::mat4& value);
        void MultWorldMatrix(const Math::mat4& value);
        const Math::mat4& GetWorldMatrix() const;
        const Math::mat4& GetLocalMatrix() const;
        const Math::mat4& GetViewMatrix() const;
        const Math::mat4& GetProjectionMatrix() const;

        //  COLORS
        void SetDiffuseColor(const Math::vec4& value);
        void SetDiffuseColor(float r, float g, float b, float a);
        void SetTextColor(const Math::vec4& value);
        void SetTextColor(float r, float g, float b, float a);
        void SetSpecularColor(const Math::vec4& value);
        const Math::vec4& GetSpecularColor() const;
        void SetSpecularFactor(float value);
        void SetAmbientColor(float value);
        const Math::vec4& GetDiffuseColor() const;

        //  MAPS
        void SetSpecularMap(ITexture2D* value, int slot);
        void SetBumpMap(ITexture2D* value, int slot);
        void SetDiffuseMap(int index, ITexture2D* value, int slot);
        void SetHeightMap(ITexture2D* value, int slot);
        void SetNormalMap(ITexture2D* value, int slot);
        void SetTextMap(ITexture2D* value, int slot);
        void SetFontMap(ITexture2D* value, int slot);
        const ITexture2D* GetDiffuseMap(int index) const;
        const ITexture2D* GetSpecularMap() const;
        const ITexture2D* GetBumpMap() const;
		
        void CastShadows(bool value);
		void ReceiveShadow(bool value);
		void EndRendering();

		void EnableBlending(bool value);
		void EnableDepthTest(bool value);		
        void EnableDiffuseShading(bool value);
        void EnableSpecularShading(bool value);
        //void EnableBumpMapping(bool value);
		void EnableSkinning(bool value);
		void EnableWireframe(bool value);
		void EnableTerrainRendering(bool value);
		void EnableLighting(bool value);
        bool IsLightingEnabled() const;
        void EnableShadows(bool value);
		void EnableTexturing(bool value);
		void EnableFontRendering(bool value);        
        void EnableBoundBoxRendering(bool value);
        void EnableDepthRendering(bool value);
        bool IsEnabledBoundingBoxRendering() const;
        void EnableBoundingSphereRendering(bool value);
        bool IsEnabledBoundingSphereRendering() const;
        void EnableNaviMeshRendering(bool value);
        bool IsEnabledNaviMeshRendering();

        //  added on 01.05.2013		
		void SetClearColor(const Math::vec4& value);
		void SetClearColor(float r, float g, float b, float a);
		void SetClearDepth(float value);

        void SetShadowModel(ShadowModel value);
        void SetShadowMapSize(const Math::ivec2& value);
        void SetShadowMapSize(int width, int height);
        void SetTexture2DArray(ITexture2DArray* value, int slot);
        //  index in current texture 2d array
        void SetShadowMapIndex(int shadow_map, int index);
        void SetDiffuseMapIndex(int diffuse_map, int index);
        void SetNormalMapIndex(int index);
        void SetShadowMaps(ITexture2DArray* value);


        const Math::vec4 GetClearColor() const;

		void Clear(bool color, bool depth, bool stencil);

        //  added on 02.05.2013
		void EnablePerVertexColor(bool value);

		void SetLightModel(LightModel value);
		LightParameters& Light(int slot);

		void DrawLine(const Math::vec3& start, const Math::vec3& end);
        void DrawLine(float x1, float y1, float x2, float y2);
        void DrawPoint(float x, float y);
        void DrawPoint(const Math::vec3& v);
        void DrawPoint(float x, float y, float z);
        void DrawCircleXY(float x, float y, float z, float r);
        void DrawCircleXY(const Math::vec3& c, float r);
        void DrawQuad(float x, float y, float width, float height);
        void DrawQuad(const Math::Rect& rect);
        void DrawText2D(float x, float y, const Core::String& value);
        void DrawText2D(float x, float y, float width, float height, const Core::String& value);
        void DrawText2D(const Math::vec2& pos, const Core::String& value);
        void DrawText2D(const Math::vec2& pos, const Math::vec2& size, const Core::String& value);
        void DrawText3D(float x, float y, float z, const Core::String& value);
        void DrawText3D(const Math::vec3& pos, const Core::String& value);
        void DrawAxis(float scale = 10);

		void SetBlendColor(const Math::vec4& value);
		void SetBlendColor(float r, float g, float b, float a);
		void SetBlendFunc(BlendFunction src, BlendFunction dst);

		FogDescription& Fog();
		const FogDescription& Fog() const;

		void PushAllState();
		void PopAllState();

		void PushViewState();
		void PopViewState();

		void PushLightState();
		void PopLightState();

		void PushRenderState();
		void PopRenderState();

		void PushBatchState();
		void PopBatchState();

		void PushTextureState();
		void PopTextureState();

        IVideoDriver* GetVideoDriver() const;
        std::vector<Batch*>& GetBatches();
        const std::vector<Batch*>& GetBatches() const;

        const Math::vec2 FindZRange(const Math::mat4& view) const;

	private:

		CoreState* Top();
		const CoreState* Top() const;

    private:
		//	next should be delete in destructor
		std::stack<CoreState*> m_state;

        //	next should not be deleted in destructor
        IFrameBuffer* m_current_frame_buffer;
        IVideoDriver* m_driver;
		std::vector<Batch*> m_batches;
        std::vector<ITextSurface*> m_texts;
        ITexture2DArray* m_shadow_maps;
	private:
		//	driver can create frames
        Frame(IVideoDriver* driver);

		Frame(const Frame&) = delete;
		Frame& operator = (const Frame&) = delete;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_COMMON_RENDER_FRAME
