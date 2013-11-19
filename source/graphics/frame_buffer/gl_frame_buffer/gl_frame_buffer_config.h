#ifndef GL_FRAME_BUFFER_CONFIG_H
#define GL_FRAME_BUFFER_CONFIG_H

#include "string/string.h"
#include "opengl/gl/glcorearb.h"

namespace Gpu
{
    class FrameBufferConfig;

    namespace OpenGL
    {
        class GlFrameBufferConfig
        {
        public:
            GlFrameBufferConfig(FrameBufferConfig* value);

            const System::string& Name() const;
            void Name(const System::string& value);

            GLenum ColorFormat() const;
            void ColorFormat(GLenum value);

            GLenum DepthFormat() const;
            void DepthFormat(GLenum value);

            int RedBitsCount() const;
            void RedBitsCount(int value);

            int DepthBitsCount() const;
            void DepthBitsCount(int value);

            int DepthSamples() const;
            void DepthSamples(int value);

            int CoverageSamples() const;
            void CoverageSamples(int value);

            unsigned Width() const;
            void Width(unsigned value);

            unsigned Height() const;
            void Height(unsigned value);

        private:
            FrameBufferConfig* m_config;
        };
    }
}

#endif // GL_FRAME_BUFFER_CONFIG_H
