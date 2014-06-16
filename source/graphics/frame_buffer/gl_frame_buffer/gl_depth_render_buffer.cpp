#include <graphics/video_driver/gl_video_driver/module.h>
#include <graphics/video_driver/module.h>
#include <graphics/texture/gl_texture/module.h>
#include <graphics/opengl/module.h>
#include "gl_depth_render_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        GlDepthRenderBuffer::GlDepthRenderBuffer(const FrameBufferConfig& c, IVideoDriver* driver)
            : DepthRenderBuffer(driver)
            , m_buffer(0) {
            FrameBufferConfig config = c;
            GL_CALL(glGenRenderbuffers(1, &m_buffer));
            Bind();
            if (driver->GetSettings()->IsEnabledCoverageSampling() && config.CoverageSamples() > config.DepthSamples()) {
                GL_CALL(glRenderbufferStorageMultisampleCoverageNV(
                            GL_RENDERBUFFER, config.CoverageSamples(), config.DepthSamples(),
                            Convert(config.DepthFormat()), config.Width(), config.Height()));
                //  update config;  TODO: Maybe it should be removed
                GLint value;
                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_COVERAGE_SAMPLES_NV, &value));
                if (value < config.CoverageSamples())
					throw Error::OpenGLUnsupportedCoverageSamplesCount(L"Failed to create color render buffer with " + config.Name() + L" config");
                else
                    config.CoverageSamples(value);

                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_COLOR_SAMPLES_NV, &value));
                if (value < config.DepthSamples())
					throw Error::OpenGLUnsupportedDepthSamplesCount(L"Failed to create color render buffer with " + config.Name() + L" config");
                else
                    config.DepthSamples(value);
            }
            else {
                GLint max_samples;
                GL_CALL(glGetIntegerv(GL_MAX_SAMPLES, &max_samples));
                if (max_samples < config.DepthSamples())
					throw Error::OpenGLUnsupportedDepthSamplesCount(L"Failed to create color render buffer with " + config.Name() + L" config");
                GL_CALL(glRenderbufferStorageMultisample(GL_RENDERBUFFER, config.DepthSamples(), Convert(config.DepthFormat())
                                                         , config.Width(), config.Height()));
                GLint value;
                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &value));
                if (value < config.DepthSamples())
					throw Error::OpenGLUnsupportedDepthSamplesCount(L"Failed to create color render buffer with " + config.Name() + L" config");
                else
                    config.DepthSamples(value);
            }
            Unbind();
        }

        void GlDepthRenderBuffer::Bind()
        {
            GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_buffer));
        }

        void GlDepthRenderBuffer::Unbind()
        {
            GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_buffer));
        }

        GlDepthRenderBuffer::~GlDepthRenderBuffer()
        {
            if (m_buffer)
            {
                GL_CALL(glDeleteRenderbuffers(1, &m_buffer));
                m_buffer = 0;
            }
        }

        GLuint GlDepthRenderBuffer::Index() const
        {
            return m_buffer;
        }
    }
}
PUNK_ENGINE_END
