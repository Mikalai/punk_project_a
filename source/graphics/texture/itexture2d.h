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

	DECLARE_PUNK_GUID(IID_ITexture2D, "42ECD9F3-6028-4396-B242-974EC637607A");
	DECLARE_PUNK_GUID(CLSID_Texture2D, "8D557D62-30C8-462C-B1C7-1A8ED4454D22");

    class ITexture2D : public ITexture {
    public:
		virtual void Initialize(ImageModule::ImageFormat internalformat, std::uint32_t width, std::uint32_t height, std::int32_t border, ImageModule::ImageFormat format, ImageModule::DataType type, const void *pixels, bool use_mipmaps, IVideoDriver* driver) = 0;
		virtual void Initialize(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, ImageModule::DataType type, const void* data, bool use_mipmaps, IVideoDriver* driver) = 0;
		virtual void Initialize(int width, int height, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver) = 0;
		virtual void Initialize(int width, int height, ImageModule::ImageFormat internal_format, ImageModule::ImageFormat format, const void* data, bool use_mipmaps, IVideoDriver* driver) = 0;
		virtual void Initialize(const ImageModule::IImage* image, bool use_mipmaps, IVideoDriver* driver) = 0;
		virtual void Initialize(const Core::String& path, bool use_mipmaps, IVideoDriver* driver) = 0;
		virtual void Initialize(Core::Buffer* buffer, bool use_mip_maps, IVideoDriver* driver) = 0;
		virtual void Initialize(const ImageModule::IImage* mage, ImageModule::ImageFormat internal_format, bool use_mipmaps, IVideoDriver* driver) = 0;		
        virtual void CopyFromCpu(std::int32_t x, std::int32_t y, std::uint32_t width, std::uint32_t height, const void* data) = 0;
        virtual void Resize(std::uint32_t width, std::uint32_t height) = 0;
        virtual void Fill(std::uint8_t data) = 0;
        virtual std::uint32_t GetHeight() const = 0;
        virtual std::uint32_t GetWidth() const = 0;
        virtual void* Map() = 0;
        virtual void Unmap(void* data) = 0;
    };

    using ITexture2DPointer = Core::Pointer<ITexture2D>;

    
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_Graphics_TEXTURE_2D
