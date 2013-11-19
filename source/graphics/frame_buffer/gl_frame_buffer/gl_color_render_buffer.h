#ifndef GL_COLOR_RENDER_BUFFER_H
#define GL_COLOR_RENDER_BUFFER_H

#include "gpu/common/frame_buffer/color_render_buffer.h"
#include "opengl/gl/glcorearb.h"

namespace Gpu
{
    class FrameBufferConfig;

    namespace OpenGL
    {
        class GlVideoDriverProxy;

        class GlColorRenderBuffer : public ColorRenderBuffer
        {
        public:
            /**
             * @brief OpenGLColorRenderBuffer create an opengl color buffer, compatible with
             * frame buffer with current config
             * @param driver
             */
            GlColorRenderBuffer(FrameBufferConfig* config, GlVideoDriverProxy* driver);
            virtual ~GlColorRenderBuffer();

            virtual void Bind() override;
            virtual void Unbind() override;

            GLuint Index();
        private:
            GLuint m_buffer;
        };
    }
}

#endif // GL_COLOR_RENDER_BUFFER_H
