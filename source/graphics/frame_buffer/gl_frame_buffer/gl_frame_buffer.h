#ifndef GL_FRAMEBUFFERIMPL_H
#define GL_FRAMEBUFFERIMPL_H

#include <graphics/frame_buffer/frame_buffer.h>
#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    namespace OpenGL {

        class GlVideoDriver;
        class GlColorRenderBuffer;
        class GlDepthRenderBuffer;

        class GlFrameBuffer : public FrameBuffer {
        public:
            using FrameBuffer::Config;

        public:
            GlFrameBuffer(IVideoDriver *driver);
            virtual ~GlFrameBuffer();
            void Bind() override;
            void Unbind() override;
            void Config(const FrameBufferConfig& config) override;
            void AttachColorTarget(std::uint32_t index, ITexture2D* buffer) override;
            void AttachColorTarget(size_t index, IRenderBuffer* buffer) override;
            void AttachDepthTarget(ITexture2D* buffer) override;
            void AttachDepthTarget(IRenderBuffer* buffer) override;
            void AttachDepthTarget(ITexture2DArray *buffer, size_t index) override;
            void SetRenderTarget(FrameBufferTarget value) override;
            void SetViewport(int x, int y, int width, int height) override;
            void SetClearFlag(bool color, bool depth, bool stencil) override;
            void SetClearColor(float r, float g, float b, float a) override;
            void SetClearColor(const Math::vec4& value) override;
            void SetClearDepth(float depth) override;
            void Clear() override;
            void SetPolygonOffset(float a, float b) override;

            static GlFrameBuffer Backbuffer;

        private:
            void Destroy();
            void CheckConfigCompatibility();
            void Check();

        private:
            GlColorRenderBuffer* m_color_rb {nullptr};
            GlDepthRenderBuffer* m_depth_rb {nullptr};
            GlFrameBuffer* m_resolve_rb {nullptr};
            GLuint m_fb {0};
            GLuint m_prev_fb {0};
            bool m_clear_depth {true};
            bool m_clear_color {true};
            bool m_clear_stencil {true};
        };
    }
}
PUNK_ENGINE_END

#endif // GL_FRAMEBUFFERIMPL_H
