#include <graphics/texture/module.h>
#include "frame_buffer.h"
#include "frame_buffer_config.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    FrameBuffer::FrameBuffer(IVideoDriver *driver)
        : m_config{nullptr}
        , m_driver{driver}
        , m_color_texture{nullptr}
        , m_depth_texture{nullptr} {}

    FrameBuffer::~FrameBuffer() {
        Constructor::DestroyTexture2D(m_color_texture);
        m_color_texture = nullptr;
        Constructor::DestroyTexture2D(m_depth_texture);
        m_depth_texture = nullptr;
        delete m_config;
        m_config = nullptr;
    }

    ITexture2D* FrameBuffer::GetColorTexture() {
        return m_color_texture;
    }

    ITexture2D* FrameBuffer::GetDepthTexture() {
        return m_depth_texture;
    }

    void FrameBuffer::Bind() {
    }

    void FrameBuffer::Unbind() {
    }

    IVideoDriver* FrameBuffer::GetVideoDriver() {
        return m_driver;
    }

    FrameBufferConfig* FrameBuffer::Config() const {
        return m_config;
    }

    void FrameBuffer::Config(const FrameBufferConfig& config) {
        if (m_config)
            delete m_config;
        m_config = new FrameBufferConfig(config);
    }    
}
PUNK_ENGINE_END
