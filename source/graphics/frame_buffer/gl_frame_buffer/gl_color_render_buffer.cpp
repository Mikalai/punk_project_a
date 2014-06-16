#include <graphics/video_driver/module.h>
#include <graphics/video_driver/gl_video_driver/module.h>
#include <graphics/texture/gl_texture/module.h>
#include <graphics/frame_buffer/module.h>
#include "gl_color_render_buffer.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        GlColorRenderBuffer::GlColorRenderBuffer(const FrameBufferConfig& c, IVideoDriver *driver)
            : ColorRenderBuffer(driver)
            , m_buffer(0)
        {
            FrameBufferConfig config = c;
            GL_CALL(glGenRenderbuffers(1, &m_buffer));
            Bind();
            if (driver->GetSettings()->IsEnabledCoverageSampling()
                    && config.CoverageSamples() > config.DepthSamples())
            {
                GL_CALL(glRenderbufferStorageMultisampleCoverageNV(
                            GL_RENDERBUFFER, config.CoverageSamples(),
                            config.DepthSamples(), Convert(config.ColorFormat()),
                            config.Width(), config.Height()));

                //  update config;  TODO: Maybe it should be removed
                GLint value;
                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_COVERAGE_SAMPLES_NV, &value));
                if (value < config.CoverageSamples())
					throw Error::OpenGLUnsupportedCoverageSamplesCount(Core::String(L"Failed to create color render buffer with {0} config").arg(config.Name()));
                else
                    config.CoverageSamples(value);

                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_COLOR_SAMPLES_NV, &value));
                if (value < config.DepthSamples())
					throw Error::OpenGLUnsupportedDepthSamplesCount(L"Failed to create color render buffer with " + config.Name() + L" config");
                else
                    config.DepthSamples(value);
            }
            else
            {
                GLint max_samples;
                GL_CALL(glGetIntegerv(GL_MAX_SAMPLES, &max_samples));
                if (max_samples < config.DepthSamples())
					throw Error::OpenGLUnsupportedDepthSamplesCount(L"Failed to create color render buffer with " + config.Name() + L" config");
                GL_CALL(glRenderbufferStorageMultisample(GL_RENDERBUFFER, config.DepthSamples(),
                                                         Convert(config.ColorFormat()), config.Width(), config.Height()));
                GLint value;
                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &value));
                if (value < config.DepthSamples())
					throw Error::OpenGLUnsupportedDepthSamplesCount(L"Failed to create color render buffer with " + config.Name() + L" config");
                else
                    config.DepthSamples(value);
            }
            Unbind();
        }

        void GlColorRenderBuffer::Bind()
        {
            GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_buffer));
        }

        void GlColorRenderBuffer::Unbind()
        {
            GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_buffer));
        }

        GlColorRenderBuffer::~GlColorRenderBuffer()
        {
            if (m_buffer)
            {
                GL_CALL(glDeleteRenderbuffers(1, &m_buffer));
                m_buffer = 0;
            }
        }

        GLuint GlColorRenderBuffer::Index()
        {
            return m_buffer;
        }
    }
}
PUNK_ENGINE_END
