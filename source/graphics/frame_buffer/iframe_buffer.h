#ifndef IFRANE_BUFFER_H
#define IFRANE_BUFFER_H

#include <config.h>
#include <cstdint>
#include "frame_buffer_target.h"

PUNK_ENGINE_BEGIN
namespace Math { class vec4; }
namespace Graphics {
    class IVideoDriver;
    class ITexture2D;
    class FrameBufferConfig;
    class IRenderBuffer;
    class ITexture2DArray;

    class IFrameBuffer {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Config(const FrameBufferConfig& config) = 0;
        virtual void AttachColorTarget(std::uint32_t index, ITexture2D* buffer) = 0;
        virtual void AttachColorTarget(size_t index, IRenderBuffer* buffer) = 0;
        virtual void AttachDepthTarget(ITexture2D* buffer) = 0;
        virtual void AttachDepthTarget(IRenderBuffer* buffer) = 0;
        virtual void AttachDepthTarget(ITexture2DArray *buffer, size_t index) = 0;
        virtual void SetRenderTarget(FrameBufferTarget value) = 0;
        virtual void SetViewport(int x, int y, int width, int height) = 0;
        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        virtual void SetClearColor(const Math::vec4& value) = 0;
        virtual void SetClearDepth(float depth) = 0;
        virtual void Clear(bool color, bool depth, bool stencil) = 0;
        virtual void SetPolygonOffset(float a, float b) = 0;
        virtual IVideoDriver* GetVideoDriver() = 0;
        virtual ITexture2D* GetColorTexture() = 0;
        virtual ITexture2D* GetDepthTexture() = 0;
        virtual FrameBufferConfig* Config() const = 0;
    };

    namespace Constructor {
        extern "C" PUNK_ENGINE_API IFrameBuffer* CreateFrameBuffer(IVideoDriver* driver);
        extern "C" PUNK_ENGINE_API IFrameBuffer* GetBackbuffer();
        extern "C" PUNK_ENGINE_API void DestroyFrameBuffer(IFrameBuffer* buffer);
    }
}
PUNK_ENGINE_END

#endif // IFRANE_BUFFER_H
