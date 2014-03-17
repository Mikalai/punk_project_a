#ifndef FRAME_BUFFER_CONFIG_H
#define FRAME_BUFFER_CONFIG_H

#include <string/module.h>
#include <images/formats.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    class FrameBufferConfig
    {
    public:
        FrameBufferConfig();

        const Core::String& Name() const;
        void Name(const Core::String& value);

        Image::ImageFormat ColorFormat() const;
        void ColorFormat(Image::ImageFormat value);

        Image::ImageFormat DepthFormat() const;
        void DepthFormat(Image::ImageFormat value);

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
        Core::String m_name;
        Image::ImageFormat m_color_format;
        Image::ImageFormat m_depth_format;
        int m_red_bits;
        int m_depth_bits;
        int m_depth_samples;
        int m_coverage_samples;
        unsigned m_width;
        unsigned m_height;
    };
}
PUNK_ENGINE_END

#endif // FRAME_BUFFER_CONFIG_H
