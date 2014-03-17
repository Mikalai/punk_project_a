#include "render_buffer_config.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    RenderBufferConfig::RenderBufferConfig()
    {}

    void RenderBufferConfig::Name(const Core::String& value) {
        m_name = value;
    }

    const Core::String& RenderBufferConfig::Name() const {
        return m_name;
    }

    void RenderBufferConfig::Format(Image::ImageFormat value) {
        m_format = value;
    }

    Image::ImageFormat RenderBufferConfig::Format() const {
        return m_format;
    }

    void RenderBufferConfig::Bits(int value) {
        m_bits = value;
    }

    int RenderBufferConfig::Bits() const {
        return m_bits;
    }
}
PUNK_ENGINE_END
