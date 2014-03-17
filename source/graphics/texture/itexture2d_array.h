#ifndef TEXTURE2D_ARRAY_H
#define TEXTURE2D_ARRAY_H

#include "itexture.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IVideoDriver;
    class ITexture2DArray : public ITexture {};

    namespace Constructor {
        extern "C" PUNK_ENGINE_API ITexture2DArray* CreateTexture2DArray(std::uint32_t width, std::uint32_t height, std::uint32_t size, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void *data, bool use_mipmaps, IVideoDriver *driver);
        extern "C" PUNK_ENGINE_API void DestroyTexture2DArray(ITexture2DArray* value);
    }
}
PUNK_ENGINE_END

#endif // TEXTURE2D_ARRAY_H
