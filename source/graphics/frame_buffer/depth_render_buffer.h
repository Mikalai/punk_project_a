#ifndef DEPTH_RENDER_BUFFER_H
#define DEPTH_RENDER_BUFFER_H

#include "render_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class DepthRenderBuffer : public RenderBuffer {
    public:
        DepthRenderBuffer(IVideoDriver* driver);
        DepthRenderBuffer(const RenderBuffer&) = delete;
        DepthRenderBuffer& operator = (const DepthRenderBuffer&) = delete;
        virtual ~DepthRenderBuffer();
    };
}
PUNK_ENGINE_END

#endif // DEPTH_RENDER_BUFFER_H
