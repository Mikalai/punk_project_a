#ifndef _H_PUNK_COMMON_RENDER_FRAME_INTERFACE
#define _H_PUNK_COMMON_RENDER_FRAME_INTERFACE

#include <memory>
#include <config.h>
#include <core/iobject.h>
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
    class ILowLevelRender;

    class Batch;

	DECLARE_PUNK_GUID(IID_IFrame, "AF81422A-F379-418D-B869-7BC24216080F");

    class IFrame : public Core::IObject
    {
    public:

        virtual ILowLevelRender* GetRender() = 0;
		virtual void SetRender(ILowLevelRender* render) = 0;
        virtual void Submit(Core::Pointer<IRenderable> value) = 0;
        virtual void SetClipSpace(const Math::ClipSpace& value) = 0;
        virtual const Math::ClipSpace& GetClipSpace() const = 0;
        virtual void SetLineWidth(float value) = 0;
        virtual void SetPointSize(float value) = 0;
        virtual void SetBoundingSphere(const Math::BoundingSphere& value) = 0;

        //  MATRIX
        virtual void SetBoneMatrix(int bone_index, const Math::mat4& value) = 0;
        virtual const Math::mat4& GetBoneMatrix(int bone_index) const = 0;
        virtual void SetTextureMatrix(const Math::mat4& value) = 0;
        virtual void SetLocalMatrix(const Math::mat4& value) = 0;
        virtual void SetWorldMatrix(const Math::mat4& value) = 0;
        virtual void SetViewMatrix(const Math::mat4& value) = 0;
        virtual void SetProjectionMatrix(const Math::mat4& value) = 0;
        virtual void MultWorldMatrix(const Math::mat4& value) = 0;
        virtual const Math::mat4& GetWorldMatrix() const = 0;
        virtual const Math::mat4& GetLocalMatrix() const = 0;
        virtual const Math::mat4& GetViewMatrix() const = 0;
        virtual const Math::mat4& GetProjectionMatrix() const = 0;
		virtual void SetArmatureMatrix(const Math::mat4& value) = 0;
		virtual const Math::mat4& GetArmatureMatrix() const = 0;
		virtual void SetOffsetMatrix(const Math::mat4& value) = 0;
		virtual const Math::mat4& GetOffsetMatrix() const = 0;
		virtual const Math::mat4& GetLastLocalMatrix() const = 0;

        //  COLORS
        virtual void SetDiffuseColor(const Math::vec4& value) = 0;
        virtual void SetDiffuseColor(float r, float g, float b, float a) = 0;
        virtual void SetTextColor(const Math::vec4& value) = 0;
        virtual void SetTextColor(float r, float g, float b, float a) = 0;
        virtual void SetSpecularColor(const Math::vec4& value) = 0;
        virtual const Math::vec4& GetSpecularColor() const = 0;
        virtual void SetSpecularFactor(float value) = 0;
        virtual void SetAmbientColor(float value) = 0;
        virtual const Math::vec4& GetDiffuseColor() const = 0;

        //  MAPS
        virtual void SetSpecularMap(ITexture2D* value, int slot) = 0;
        virtual void SetBumpMap(ITexture2D* value, int slot) = 0;
        virtual void SetDiffuseMap(int index, ITexture2D* value, int slot) = 0;
        virtual void SetHeightMap(ITexture2D* value, int slot) = 0;
        virtual void SetNormalMap(ITexture2D* value, int slot) = 0;
        virtual void SetTextMap(ITexture2D* value, int slot) = 0;
        virtual void SetFontMap(ITexture2D* value, int slot) = 0;
        virtual const ITexture2D* GetDiffuseMap(int index) const = 0;
        virtual const ITexture2D* GetSpecularMap() const = 0;
        virtual const ITexture2D* GetBumpMap() const = 0;

        virtual void CastShadows(bool value) = 0;
        virtual void ReceiveShadow(bool value) = 0;
        virtual void EndRendering() = 0;

        virtual void EnableBlending(bool value) = 0;
        virtual void EnableDepthTest(bool value) = 0;
        virtual void EnableDiffuseShading(bool value) = 0;
        virtual void EnableSpecularShading(bool value) = 0;
        //void EnableBumpMapping(bool value) = 0;
        virtual void EnableSkinning(bool value) = 0;
		virtual bool IsEnabledSkinning() const = 0;
        virtual void EnableWireframe(bool value) = 0;
        virtual void EnableTerrainRendering(bool value) = 0;
        virtual void EnableLighting(bool value) = 0;
        virtual bool IsLightingEnabled() const = 0;
        virtual void EnableShadows(bool value) = 0;
        virtual void EnableTexturing(bool value) = 0;
        virtual void EnableFontRendering(bool value) = 0;
        virtual void EnableBoundBoxRendering(bool value) = 0;
        virtual void EnableDepthRendering(bool value) = 0;
        virtual bool IsEnabledBoundingBoxRendering() const = 0;
        virtual void EnableBoundingSphereRendering(bool value) = 0;
        virtual bool IsEnabledBoundingSphereRendering() const = 0;
        virtual void EnableNaviMeshRendering(bool value) = 0;
        virtual bool IsEnabledNaviMeshRendering() = 0;

        //  added on 01.05.2013
        virtual void SetClearColor(const Math::vec4& value) = 0;
        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        virtual void SetClearDepth(float value) = 0;

        virtual void SetShadowModel(ShadowModel value) = 0;
        virtual void SetShadowMapSize(const Math::ivec2& value) = 0;
        virtual void SetShadowMapSize(int width, int height) = 0;
        virtual void SetTexture2DArray(ITexture2DArray* value, int slot) = 0;
        //  index in current texture 2d array
        virtual void SetShadowMapIndex(int shadow_map, int index) = 0;
        virtual void SetDiffuseMapIndex(int diffuse_map, int index) = 0;
        virtual void SetNormalMapIndex(int index) = 0;
        virtual void SetShadowMaps(ITexture2DArray* value) = 0;


        virtual const Math::vec4 GetClearColor() const = 0;

        //virtual void Clear(bool color, bool depth, bool stencil) = 0;

        //  added on 02.05.2013
        virtual void EnablePerVertexColor(bool value) = 0;

        virtual void SetLightModel(LightModel value) = 0;
        virtual LightParameters& Light(int slot) = 0;

        virtual void DrawLine(const Math::vec3& start, const Math::vec3& end) = 0;
        virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;
        virtual void DrawPoint(float x, float y) = 0;
        virtual void DrawPoint(const Math::vec3& v) = 0;
        virtual void DrawPoint(float x, float y, float z) = 0;
        virtual void DrawCircleXY(float x, float y, float z, float r) = 0;
        //virtual void DrawCircleXY(const Math::vec3& c, float r) = 0;
        virtual void DrawQuad(float x, float y, float width, float height) = 0;
        virtual void DrawQuad(const Math::Rect& rect) = 0;
        virtual void DrawText2D(float x, float y, const Core::String& value) = 0;
//        virtual void DrawText2D(float x, float y, float width, float height, const Core::String& value) = 0;
//        virtual void DrawText2D(const Math::vec2& pos, const Core::String& value) = 0;
        virtual void DrawText2D(const Math::vec2& pos, const Math::vec2& size, const Core::String& value) = 0;
//        virtual void DrawText3D(float x, float y, float z, const Core::String& value) = 0;
//        virtual void DrawText3D(const Math::vec3& pos, const Core::String& value) = 0;
        virtual void DrawAxis(float scale = 10) = 0;

        virtual void SetBlendColor(const Math::vec4& value) = 0;
        virtual void SetBlendColor(float r, float g, float b, float a) = 0;
        virtual void SetBlendFunc(BlendFunction src, BlendFunction dst) = 0;

        virtual FogDescription& Fog() = 0;
        virtual const FogDescription& Fog() const = 0;

        virtual void PushAllState() = 0;
        virtual void PopAllState() = 0;

        virtual void PushViewState() = 0;
        virtual void PopViewState() = 0;

        virtual void PushLightState() = 0;
        virtual void PopLightState() = 0;

        virtual void PushRenderState() = 0;
        virtual void PopRenderState() = 0;

        virtual void PushBatchState() = 0;
        virtual void PopBatchState() = 0;

        virtual void PushTextureState() = 0;
        virtual void PopTextureState() = 0;

        virtual IVideoDriver* GetVideoDriver() const = 0;
		virtual IRenderableBuilder* GetRenderableBuilder() = 0;

        virtual const Math::vec2 FindZRange(const Math::mat4& view) const = 0;
    };

	using IFramePointer = Core::Pointer < IFrame > ;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_COMMON_RENDER_FRAME_INTERFACE
