#ifndef IVIDEO_MEMORY_H
#define IVIDEO_MEMORY_H

#include <config.h>
#include <cstdint>

#include <memory>
#include <vector>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class IVideoMemory
    {
    public:
        virtual void SetMaxMemoryUsage(std::uint32_t value) = 0;
        virtual std::uint32_t GetMaxMemoryUsage() const = 0;
        virtual std::uint32_t GetMemoryUsage() const = 0;
        virtual std::uint32_t GetMaxAvailableMemory() const = 0;
        //virtual IBufferObject* AllocatePixelBuffer(std::uint32_t size) = 0;
        //virtual void FreePixelBuffer(IBufferObject* value) = 0;
        //virtual IBufferObject* AllocateVertexBuffer(std::uint32_t size) = 0;
        //virtual void FreeVertexBuffer(IBufferObject* value) = 0;
        //virtual IBufferObject* AllocateIndexBuffer(std::uint32_t size) = 0;
        //virtual void FreeIndexBuffer(IBufferObject* value) = 0;
    };

    namespace Constructor {
        extern "C" PUNK_ENGINE_API IVideoMemory* GetVideoMemory();
        extern "C" PUNK_ENGINE_API void DestroyVideoMemory();
    }
}
PUNK_ENGINE_END

#endif // IVIDEO_MEMORY_H
