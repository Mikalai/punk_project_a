#ifndef _H_PUNK_OPENGL_RENDERABLE_INTERFACE
#define _H_PUNK_OPENGL_RENDERABLE_INTERFACE

#include <memory>
#include <config.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class PUNK_ENGINE_API IRenderable {
	public:
        virtual void Bind(std::int64_t) = 0;
        virtual void Unbind() = 0;
        virtual void Render() = 0;
        virtual std::uint64_t GetMemoryUsage() = 0;
        virtual bool HasData() const = 0;
	};

    using IRenderableUniquePtr = std::unique_ptr<IRenderable, void (*)(IRenderable*)>;

    extern PUNK_ENGINE_API void DestroyRenderable(IRenderable* value);
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_RENDERABLE
