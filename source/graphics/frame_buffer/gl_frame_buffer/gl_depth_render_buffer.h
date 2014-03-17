#ifndef PUNK_OPENGL_DEPTH_BUFFER_H
#define PUNK_OPENGL_DEPTH_BUFFER_H

#include <graphics/frame_buffer/depth_render_buffer.h>
#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class FrameBufferConfig;
    class GlVideoDriver;

    namespace OpenGL {

        class PUNK_ENGINE_LOCAL GlDepthRenderBuffer : public DepthRenderBuffer {
        public:

            GlDepthRenderBuffer(const FrameBufferConfig& config, IVideoDriver* driver);
            virtual ~GlDepthRenderBuffer();

            virtual void Bind() override;
            virtual void Unbind() override;

            GLuint Index() const;

        private:
            GLuint m_buffer;
        };
    }
}
PUNK_ENGINE_END

#endif // PUNK_OPENGL_GL_DEPTH_BUFFER_H
