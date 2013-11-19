#ifndef PUNK_OPENGL_DEPTH_BUFFER_H
#define PUNK_OPENGL_DEPTH_BUFFER_H

#include "gpu/common/frame_buffer/depth_render_buffer.h"
#include "opengl/gl/glcorearb.h"

namespace Gpu
{
    class FrameBufferConfig;
    class GlVideoDriverProxy;

    namespace OpenGL
    {
        class GlDepthRenderBuffer : public DepthRenderBuffer
        {
        public:

            GlDepthRenderBuffer(FrameBufferConfig* config, GlVideoDriverProxy* driver);
            virtual ~GlDepthRenderBuffer();

            virtual void Bind() override;
            virtual void Unbind() override;

            GLuint Index() const;

        private:
            GLuint m_buffer;
        };
    }
}

#endif // PUNK_OPENGL_GL_DEPTH_BUFFER_H
