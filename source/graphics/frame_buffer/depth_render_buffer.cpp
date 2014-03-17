#include "depth_render_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    DepthRenderBuffer::DepthRenderBuffer(IVideoDriver *driver)
        : RenderBuffer(driver)
    {}

    DepthRenderBuffer::~DepthRenderBuffer()
    {}
}
PUNK_ENGINE_END
