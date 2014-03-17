#ifndef _H_PUNK_Graphics_TEXTURE_2D
#define _H_PUNK_Graphics_TEXTURE_2D

#include <config.h>
#include <cstdint>
#include <images/formats.h>

#include "itexture.h"

PUNK_ENGINE_BEGIN
namespace System { class string; }
namespace Image { class Image; }
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

    namespace Constructor {
        extern "C" PUNK_ENGINE_API ITexture2D* CreateTexture2D(Image::ImageFormat internalformat, std::uint32_t width, std::uint32_t height, std::int32_t border, Image::ImageFormat format, Image::DataType type, const void *pixels, bool use_mipmaps, IVideoDriver* driver);
        extern "C" PUNK_ENGINE_API void DestroyTexture2D(ITexture2D* value);
    }
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_Graphics_TEXTURE_2D
