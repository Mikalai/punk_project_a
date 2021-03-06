#ifndef _H_PUNK_GPU_RENDERABLE_BUILDER_INTERFACE
#define _H_PUNK_GPU_RENDERABLE_BUILDER_INTERFACE

#include <memory>
#include <config.h>
#include <core/iobject.h>
#include <math/forward.h>
#include <graphics/primitives/iindex_array.h>
#include <graphics/primitives/ivertex_array.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    enum class PrimitiveType;
    class IRenderable;
    class IVideoDriver;

	DECLARE_PUNK_GUID(IID_IRenderableBuilder, "D4CAB697-87AC-4574-A088-C0A287E7AFE5");
	DECLARE_PUNK_GUID(CLSID_RenderableBuilder, "D4CAB697-87AC-4574-A088-C0A287E7AFE5");

    class IRenderableBuilder : public Core::IObject
    {
    public:
		virtual void Initialize(IVideoDriver* driver) = 0;
        virtual void Begin(const PrimitiveType& value) = 0;
        virtual void Vertex3f(float x, float y, float z) = 0;
        virtual void Vertex3fv(const float* value) = 0;
        virtual void Vertex3fv(const Math::vec3& value) = 0;
        virtual void Color3f(float r, float g, float b) = 0;
        virtual void Color3fv(const float* value) = 0;
        virtual void Color3fv(const Math::vec3& value) = 0;
        virtual void TexCoord2f(float x, float y) = 0;
        virtual void TexCoord2fv(const float* value) = 0;
        virtual void TexCoord2fv(const Math::vec2& value) = 0;
        virtual void Normal3f(float x, float y, float z) = 0;
        virtual void Normal3fv(const float* value) = 0;
        virtual void Normal3fv(const Math::vec3& value) = 0;
        virtual void End() = 0;
        virtual const Math::BoundingSphere* GetBoundingSphere() const = 0;
        virtual bool IsValid() const = 0;
		virtual Core::Pointer<IRenderable> ToRenderable() = 0;
		virtual Core::Pointer<IRenderable> ToRenderable(PrimitiveType type, Core::Pointer<IVertexArray> vb, Core::Pointer<IIndexArray> ib) = 0;
    };

	using IRenderableBuilderPointer = Core::Pointer < IRenderableBuilder > ;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_RENDERABLE_BUILDER
