#include "opengl/common/error/module.h"
#include "opengl/common/extensions.h"
#include "opengl/common/gl_proxy_video_driver.h"
#include "opengl/common/gl_capabilities.h"
#include "opengl/common/gl_video_driver.h"
#include "gl_depth_render_buffer.h"

namespace Gpu
{
    namespace OpenGL
    {
        GlDepthRenderBuffer::GlDepthRenderBuffer(FrameBufferConfig *config, GlVideoDriverProxy* driver)
            : DepthRenderBuffer(driver->GetVideoDriver())
            , m_buffer(0)
        {
            GL_CALL(glGenRenderbuffers(1, &m_buffer));
            Bind();
            if (driver->GetCaps().IsCoverageSamplingEnabled && config->CoverageSamples() > config->DepthSamples())
            {
                GL_CALL(glRenderbufferStorageMultisampleCoverageNV(
                            GL_RENDERBUFFER, config->CoverageSamples(), config->DepthSamples(),
                            ImageFormatToOpenGL(config->DepthFormat()), config->Width(), config->Height()));
                //  update config;  TODO: Maybe it should be removed
                GLint value;
                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_COVERAGE_SAMPLES_NV, &value));
                if (value < config->CoverageSamples())
                    throw System::PunkException(L"Failed to create color render buffer with " + config->Name() + L" config");
                else
                    config->CoverageSamples(value);

                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_COLOR_SAMPLES_NV, &value));
                if (value < config->DepthSamples())
                    throw System::PunkException(L"Failed to create color render buffer with " + config->Name() + L" config");
                else
                    config->DepthSamples(value);
            }
            else
            {
                GLint max_samples;
                GL_CALL(glGetIntegerv(GL_MAX_SAMPLES, &max_samples));
                if (max_samples < config->DepthSamples())
                    throw System::PunkException(L"Failed to create color render buffer with " + config->Name() + L" config");
                GL_CALL(glRenderbufferStorageMultisample(GL_RENDERBUFFER, config->DepthSamples(), ImageFormatToOpenGL(config->DepthFormat())
                                                         , config->Width(), config->Height()));
                GLint value;
                GL_CALL(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &value));
                if (value < config->DepthSamples())
                    throw System::PunkException(L"Failed to create color render buffer with " + config->Name() + L" config");
                else
                    config->DepthSamples(value);
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
