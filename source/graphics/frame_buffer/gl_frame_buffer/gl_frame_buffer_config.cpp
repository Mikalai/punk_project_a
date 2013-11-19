#include "gpu/common/frame_buffer/frame_buffer_config.h"
#include "gl_frame_buffer_config.h"

namespace Gpu
{
    namespace OpenGL
    {
        GlFrameBufferConfig::GlFrameBufferConfig(FrameBufferConfig* value)
            : m_config(value)
        {}

        const System::string& GlFrameBufferConfig::Name() const
        {
            return m_config->Name();
        }

        void GlFrameBufferConfig::Name(const System::string& value)
        {
            m_config->Name(value);
        }

        GLenum GlFrameBufferConfig::ColorFormat() const
        {
            re
        }
        void GlFrameBufferConfig::ColorFormat(ImageModule::ImageFormat value);

        ImageModule::ImageFormat GlFrameBufferConfig::DepthFormat() const;
        void GlFrameBufferConfig::DepthFormat(ImageModule::ImageFormat value);

        int GlFrameBufferConfig::RedBitsCount() const;
        void GlFrameBufferConfig::RedBitsCount(int value);

        int GlFrameBufferConfig::DepthBitsCount() const;
        void GlFrameBufferConfig::DepthBitsCount(int value);

        int GlFrameBufferConfig::DepthSamples() const;
        void GlFrameBufferConfig::DepthSamples(int value);

        int GlFrameBufferConfig::CoverageSamples() const;
        void GlFrameBufferConfig::CoverageSamples(int value);

        unsigned GlFrameBufferConfig::Width() const;
        void GlFrameBufferConfig::Width(unsigned value);

        unsigned GlFrameBufferConfig::Height() const;
        void GlFrameBufferConfig::Height(unsigned value);
    }
}
