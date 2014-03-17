#ifndef GL_COLOR_RENDER_BUFFER_H
#define GL_COLOR_RENDER_BUFFER_H

#include <graphics/frame_buffer/color_render_buffer.h>
#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    class FrameBufferConfig;
    class IVideoDriver;

    namespace OpenGL {        

        class PUNK_ENGINE_LOCAL GlColorRenderBuffer : public ColorRenderBuffer {
        public:
            /**
             * @brief OpenGLColorRenderBuffer create an opengl color buffer, compatible with
             * frame buffer with current config
             * @param driver
             */
            GlColorRenderBuffer(const FrameBufferConfig& config, IVideoDriver* driver);
            virtual ~GlColorRenderBuffer();

            virtual void Bind() override;
            virtual void Unbind() override;

            GLuint Index();
        private:
            GLuint m_buffer;
        };
    }
}
PUNK_ENGINE_END

#endif // GL_COLOR_RENDER_BUFFER_H
