#ifndef _H_PUNK_OPENGL_RENDERABLE_INTERFACE
#define _H_PUNK_OPENGL_RENDERABLE_INTERFACE

#include <memory>
#include <config.h>
#include <cstdint>
#include <core/iobject.h>
#include "ivertex_array.h"
#include "iindex_array.h"
#include "primitive_type.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

	DEFINE_PUNK_GUID(IID_IRenderable, "ED9AECD3-AC54-4F10-99E1-1A2AE3D8B6BE");

    class IRenderable : public virtual Core::IObject {
	public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Render() = 0;
        virtual std::uint64_t GetMemoryUsage() = 0;
        virtual bool HasData() const = 0;
		virtual void Cook(IVertexArray* vb, IIndexArray* ib) = 0;
	};

	using IRenderableUniquePtr = Core::UniquePtr < IRenderable > ;    
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_RENDERABLE
