#include "render_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    RenderBuffer::RenderBuffer(IVideoDriver *driver)
        : m_driver(driver)
    {}

    RenderBuffer::~RenderBuffer()
    {}

    IVideoDriver* RenderBuffer::GetVideDriver()
    {
        return m_driver;
    }

    void RenderBuffer::Bind()
    {}

    void RenderBuffer::Unbind()
    {}
}
PUNK_ENGINE_END
