#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstddef>
#include <graphics/texture/module.h>
#include "iframe_buffer.h"
#include "frame_buffer_target.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class PUNK_ENGINE_LOCAL FrameBuffer : public IFrameBuffer {
    public:
        FrameBuffer(IVideoDriver* driver);
        FrameBuffer(const FrameBuffer&) = delete;
        FrameBuffer& operator = (const FrameBuffer&) = delete;
        virtual ~FrameBuffer();
        void Bind() override;
        void Unbind() override;
        void Config(const FrameBufferConfig& config) override;        
        IVideoDriver* GetVideoDriver() override;
        ITexture2D* GetColorTexture() override;
        ITexture2D* GetDepthTexture() override;
        FrameBufferConfig* Config() const override;

    protected:
        FrameBufferConfig* m_config {nullptr};
        IVideoDriver* m_driver {nullptr};
        ITexture2DUniquePtr m_color_texture {nullptr, Core::DestroyObject};
		ITexture2DUniquePtr m_depth_texture{ nullptr, Core::DestroyObject};
    };    
}
PUNK_ENGINE_END

#endif // FRAMEBUFFER_H
