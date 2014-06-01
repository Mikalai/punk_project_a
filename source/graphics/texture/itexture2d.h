#ifndef _H_PUNK_Graphics_TEXTURE_2D
#define _H_PUNK_Graphics_TEXTURE_2D

#include <memory>
#include <config.h>
#include <cstdint>
#include <images/formats.h>

#include "itexture.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; class Buffer; }
namespace ImageModule { class IImage; }
namespace Graphics {
    class IVideoDriver;

    class PUNK_ENGINE_API ITexture2D : public ITexture {
    public:
        virtual void CopyFromCpu(std::int32_t x, std::int32_t y, std::uint32_t width, std::uint32_t height, const void* data) = 0;
        virtual void Resize(std::uint32_t width, std::uint32_t height) = 0;
        virtual void Fill(std::uint8_t data) = 0;
        virtual std::uint32_t GetHeight() const = 0;
        virtual std::uint32_t GetWidth() const = 0;
        virtual void* Map() = 0;
        virtual void Unmap(void* data) = 0;
    };

    using ITexture2DUniquePtr = std::unique_ptr<ITexture2D, void (*)(ITexture2D*)>;

    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(ImageModule::ImageFormat internalformat, std::uint32_t width, std::uint32_t height, std::int32_t border, ImageModule::ImageFormat format, ImageModule::DataType type, const void *pixels, bool use_mipmaps, IVideoDriver* driver);
    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps, IVideoDriver* driver);
    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver);
    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver);
    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(const ImageModule::IImage* image, bool use_mipmaps, IVideoDriver* driver);
    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(const Core::String& path, bool use_mipmaps, IVideoDriver* driver);
    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(Core::Buffer* buffer, bool use_mip_maps, IVideoDriver* driver);
    extern PUNK_ENGINE_API ITexture2DUniquePtr CreateTexture2D(const ImageModule::IImage* mage, ImageModule::ImageFormat internal_format, bool use_mipmaps, IVideoDriver* driver);

    extern "C" PUNK_ENGINE_API void DestroyTexture2D(ITexture2D* value);
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_Graphics_TEXTURE_2D
