#include <vector>
#include <memory.h>
#include <images/module.h>
#include <graphics/error/module.h>
#include <graphics/frame_buffer/module.h>
#include <graphics/texture/module.h>
#include <graphics/canvas/module.h>
#include <system/window/window_interface.h>
#include "ivideo_driver_settings.h"
#include "video_driver.h"

PUNK_ENGINE_BEGIN
namespace Graphics
{
    Image::ImageFormat GetInternalFormat(Image::ImageFormat format) {
        switch(format) {
        case Image::ImageFormat::ALPHA:
        case Image::ImageFormat::IMAGE_FORMAT_R32F:
        case Image::ImageFormat::RED:
            return Image::ImageFormat::RED;
        case Image::ImageFormat::RGB:
            return Image::ImageFormat::RGB;
        case Image::ImageFormat::RGBA:
            return Image::ImageFormat::RGBA;
        default:
            throw Error::GraphicsException(L"Can't find suitable internal format");
        }
    }

    ITexture2D* VideoDriver::CreateTexture2D(int width, int height, Image::ImageFormat internal_format, Image::ImageFormat format, const void* data, bool use_mipmaps) {
        return CreateTexture2D(width, height,
                               internal_format, format,
                               Image::DataType::IMAGE_DATA_TYPE_BYTE,
                               data, use_mipmaps);
    }

    ITexture2D* VideoDriver::CreateTexture2D(int width, int height, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void* data, bool use_mipmaps) {
        return Constructor::CreateTexture2D(internal_format, width, height, 0, format,
                                            type, data, use_mipmaps, this);
    }

    ITexture2D* VideoDriver::CreateTexture2D(int width, int height, Image::ImageFormat format, const void* data, bool use_mipmaps) {
        auto internal_format = GetInternalFormat(format);
        return CreateTexture2D(width, height,
                               internal_format, format,
                               Image::DataType::IMAGE_DATA_TYPE_BYTE,
                               data, use_mipmaps);
    }

    ITexture2D* VideoDriver::CreateTexture2D(const Image::Image& image, bool use_mipmaps) {
        return CreateTexture2D(image.GetWidth(),
                               image.GetHeight(),
                               image.GetImageFormat(),
                               image.GetData(),
                               use_mipmaps);
    }

    ITexture2D* VideoDriver::CreateTexture2D(const Core::String& path, bool use_mip_maps)
    {
        Image::Importer importer;
        std::unique_ptr<Image::Image> image(importer.LoadAnyImage(path));

        if (image.get())
        {
            return CreateTexture2D(*image, use_mip_maps);
        }
        else
            throw Error::GraphicsException(L"Can't create texture from " + path);
    }

    ITexture2D* VideoDriver::CreateTexture2D(Core::Buffer *buffer, bool use_mip_maps)
    {
        Image::Image image;
        image.Load(buffer);
        return CreateTexture2D(image, use_mip_maps);
    }

    ITexture2D* VideoDriver::CreateTexture2D(const Image::Image &image, Image::ImageFormat internal_format, bool use_mipmaps)
	{
        auto format = GetInternalFormat(image.GetImageFormat());
        size_t width = image.GetWidth();
        size_t height = image.GetHeight();
        void* data = (void*)image.GetData();
        std::vector<unsigned char> buffer(image.GetSizeInBytes());
        memcpy(&buffer[0], data, image.GetSizeInBytes());
        return CreateTexture2D(width, height, internal_format, format, data, use_mipmaps);
	}

    IFrameBuffer* VideoDriver::CreateFrameBuffer() {
        auto fb = GetSettings()->GetFrameBufferConfig(0);
        fb.Width(GetCanvas()->GetWindow()->GetWidth());
        fb.Height(GetCanvas()->GetWindow()->GetHeight());
        IFrameBuffer* buffer = Constructor::CreateFrameBuffer(this);
        buffer->Config(fb);
        return buffer;
    }

    IFrameBuffer* VideoDriver::CreateFrameBuffer(int width, int height)
    {
        auto fb = GetSettings()->GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        IFrameBuffer* buffer = Constructor::CreateFrameBuffer(this);
        buffer->Config(fb);
        return buffer;
    }

    IFrameBuffer* VideoDriver::CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_format)
    {
        auto fb = GetSettings()->GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        IFrameBuffer* buffer = Constructor::CreateFrameBuffer(this);
        buffer->Config(fb);
        return buffer;
    }

    IFrameBuffer* VideoDriver::CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_format, int depth_samples)
    {
        FrameBufferConfig fb = GetSettings()->GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        fb.DepthSamples(depth_samples);
        IFrameBuffer* buffer = Constructor::CreateFrameBuffer(this);
        buffer->Config(fb);
        return buffer;
    }

    IFrameBuffer* VideoDriver::CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_format, int depth_samples, int coverage_samples)
    {
        FrameBufferConfig fb = GetSettings()->GetFrameBufferConfig(0);
        fb.Width(width);
        fb.Height(height);
        fb.ColorFormat(color_format);
        fb.DepthFormat(depth_format);
        fb.DepthSamples(depth_samples);
        fb.CoverageSamples(coverage_samples);
        IFrameBuffer* buffer = Constructor::CreateFrameBuffer(this);
        buffer->Config(fb);
        return buffer;
    }    

    ITexture2DArray* VideoDriver::CreateTexture2DArray(int width, int height, int depth, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void *data, bool use_mipmaps)
    {
        return Constructor::CreateTexture2DArray(width, height, depth, internal_format, format, type, data, use_mipmaps, this);
    }

    IFrame* VideoDriver::BeginFrame()
    {
        //  TODO: Safer resource managment should be made here
        //IFrame* frame = new IFrame(this);
        return nullptr;//frame;
    }

    void VideoDriver::EndFrame(IFrame* value)
    {
        //  TODO: Safer resource managment should be made here
//        delete value;
//        SwapBuffers();
    }

    VideoDriver::~VideoDriver()
    {}    
}
PUNK_ENGINE_END
