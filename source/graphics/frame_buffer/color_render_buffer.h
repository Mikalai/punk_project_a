#ifndef COLOR_RENDER_BUFFER_H
#define COLOR_RENDER_BUFFER_H

#include <config.h>
#include "render_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class ColorRenderBuffer : public RenderBuffer
    {
    public:
        ColorRenderBuffer(IVideoDriver* driver);
        ColorRenderBuffer(const ColorRenderBuffer&) = delete;
        ColorRenderBuffer& operator = (ColorRenderBuffer&) = delete;
        virtual ~ColorRenderBuffer();
    };
}
PUNK_ENGINE_END

#endif // COLOR_RENDER_BUFFER_H
