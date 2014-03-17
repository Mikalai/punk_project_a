#include "color_render_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    ColorRenderBuffer::ColorRenderBuffer(IVideoDriver *driver)
        : RenderBuffer(driver) {}

    ColorRenderBuffer::~ColorRenderBuffer() {}
}
PUNK_ENGINE_END
