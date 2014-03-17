#ifndef _H_PUNK_VIDEO_DRIVER
#define _H_PUNK_VIDEO_DRIVER

#include "ivideo_driver.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class PUNK_ENGINE_LOCAL VideoDriver : public IVideoDriver {
	public:
        VideoDriver() = default;
        ~VideoDriver();
        ITexture2D* CreateTexture2D(int width, int height, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void* data, bool use_mipmaps) override;
        ITexture2DArray* CreateTexture2DArray(int width, int height, int depth, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void* data, bool use_mipmaps) override;
        ITexture2D* CreateTexture2D(int width, int height, Image::ImageFormat format, const void* data, bool use_mipmaps) override;
        ITexture2D* CreateTexture2D(int width, int height, Image::ImageFormat internal_format, Image::ImageFormat format, const void* data, bool use_mipmaps) override;
        ITexture2D* CreateTexture2D(const Image::Image& image, bool use_mipmaps) override;
        ITexture2D* CreateTexture2D(const Core::String& path, bool use_mipmaps) override;
        ITexture2D* CreateTexture2D(Core::Buffer* buffer, bool use_mip_maps) override;
        ITexture2D* CreateTexture2D(const Image::Image&image, Image::ImageFormat internal_format, bool use_mipmaps) override;
        IFrameBuffer* CreateFrameBuffer() override;
        IFrameBuffer* CreateFrameBuffer(int width, int height);
        IFrameBuffer* CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_color) override;
        IFrameBuffer* CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_color, int depth_samples) override;
        IFrameBuffer* CreateFrameBuffer(int width, int height, Image::ImageFormat color_format, Image::ImageFormat depth_color, int depth_samples, int coverage_samples) override;
        IFrame* BeginFrame() override;
        void EndFrame(IFrame* value) override;
	private:
        VideoDriver(const VideoDriver&) = delete;
        VideoDriver& operator = (const VideoDriver&) = delete;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIDEO_DRIVER
