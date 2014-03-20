#include <graphics/texture/module.h>
#include "frame_buffer.h"
#include "frame_buffer_config.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    FrameBuffer::FrameBuffer(IVideoDriver *driver)
        : m_config{nullptr}
        , m_driver{driver}
        , m_color_texture{nullptr, DestroyTexture2D}
        , m_depth_texture{nullptr, DestroyTexture2D} {}

    FrameBuffer::~FrameBuffer() {
        m_color_texture.reset(nullptr);
        m_depth_texture.reset(nullptr);
        delete m_config;
        m_config = nullptr;
    }

    ITexture2D* FrameBuffer::GetColorTexture() {
        return m_color_texture.get();
    }

    ITexture2D* FrameBuffer::GetDepthTexture() {
        return m_depth_texture.get();
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
