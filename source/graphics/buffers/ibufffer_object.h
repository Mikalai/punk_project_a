#ifndef _H_PUNK_OPENGL_INDEX_BUFFER_INTERFACE
#define _H_PUNK_OPENGL_INDEX_BUFFER_INTERFACE

#include <cstdint>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IVideoMemory;

    class IBufferObject {
    public:
        virtual void Create(const void* data, std::uint32_t m_size) = 0;
        virtual void Destroy() = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void* Map() = 0;
        virtual const void* Map() const = 0;
        virtual void Unmap() const = 0;
        virtual void CopyData(const void* data, std::uint32_t size) = 0;
        virtual bool IsValid() const = 0;
        virtual std::uint32_t GetSize() = 0;
    };

    namespace Constructor {
        extern "C" PUNK_ENGINE_API IBufferObject* CreatePixelBuffer(IVideoMemory* memory);
        extern "C" PUNK_ENGINE_API void DestroyPixelBuffer(IBufferObject* buffer);
        extern "C" PUNK_ENGINE_API IBufferObject* CreateVertexBuffer(IVideoMemory* memory);
        extern "C" PUNK_ENGINE_API void DestroyVertexBuffer(IBufferObject* buffer);
        extern "C" PUNK_ENGINE_API IBufferObject* CreateIndexBuffer(IVideoMemory* memory);
        extern "C" PUNK_ENGINE_API void DestroyIndexBuffer(IBufferObject* buffer);
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_INDEX_BUFFER
