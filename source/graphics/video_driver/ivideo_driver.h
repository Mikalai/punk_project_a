#ifndef _H_PUNK_VIDEO_DRIVER_INTERFACE
#define _H_PUNK_VIDEO_DRIVER_INTERFACE

#include <config.h>
#include <images/formats.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Image { class Image; }
namespace Core {
    class String;
    class Buffer;
}
namespace Graphics {

    class IRenderTarget;
    class ITexture2D;
    class ITexture2DArray;
    class IFrame;
    class FrameBufferConfig;
    class IFrameBuffer;
    class ICanvas;
    class IVideoDriverSettings;

    class PUNK_ENGINE_API IVideoDriver
	{
	public:
        virtual ICanvas* GetCanvas() = 0;
        virtual ITexture2D* CreateTexture2D(int width, int height, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void* data, bool use_mipmaps) = 0;
        virtual ITexture2DArray* CreateTexture2DArray(int width, int height, int depth, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void* data, bool use_mipmaps) = 0;        
        virtual ITexture2D* CreateTexture2D(int width, int height, Image::ImageFormat format, const void* data, bool use_mipmaps) = 0;
        virtual ITexture2D* CreateTexture2D(int width, int height, Image::ImageFormat internal_format, Image::ImageFormat format, const void* data, bool use_mipmaps) = 0;
        virtual ITexture2D* CreateTexture2D(const Image::Image& image, bool use_mipmaps) = 0;
        virtual ITexture2D* CreateTexture2D(const Core::String& path, bool use_mipmaps) = 0;
        virtual ITexture2D* CreateTexture2D(Core::Buffer* buffer, bool use_mip_maps) = 0;
        virtual ITexture2D* CreateTexture2D(const Image::Image&image, Image::ImageFormat internal_format, bool use_mipmaps) = 0;
        virtual IFrameBuffer* CreateFrameBuffer() = 0;
        virtual IFrameBuffer* CreateFrameBuffer(const FrameBufferConfig& config) = 0;
        virtual IFrameBuffer* CreateFrameBuffer(int width, int height) = 0;
        virtual IFrameBuffer* CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_color) = 0;
        virtual IFrameBuffer* CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_color, int depth_samples) = 0;
        virtual IFrameBuffer* CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_color, int depth_samples, int coverage_samples) = 0;
        virtual IFrame* BeginFrame() = 0;
        virtual void EndFrame(IFrame* value) = 0;
        virtual IVideoDriverSettings* GetSettings() = 0;
	};

    namespace Constructor {
        extern "C" PUNK_ENGINE_API IVideoDriver* CreateVideoDriver(ICanvas* canvas);
        extern "C" PUNK_ENGINE_API void DestroyVideoDriver(IVideoDriver* driver);
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIDEO_DRIVER_INTERFACE
