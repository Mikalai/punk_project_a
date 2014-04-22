#ifndef TEXTURE2D_ARRAY_H
#define TEXTURE2D_ARRAY_H

#include <memory>
#include "itexture.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IVideoDriver;
    class ITexture2DArray : public ITexture {};

    using ITexture2DArrayUniquePtr = std::unique_ptr<ITexture2DArray, void (*)(ITexture2DArray*)>;

    extern PUNK_ENGINE_API ITexture2DArrayUniquePtr CreateTexture2DArray(std::uint32_t width, std::uint32_t height, std::uint32_t size, Image::ImageFormat internal_format, Image::ImageFormat format, Image::DataType type, const void *data, bool use_mipmaps, IVideoDriver *driver);
    extern PUNK_ENGINE_API void DestroyTexture2DArray(ITexture2DArray* value);
}
PUNK_ENGINE_END

#endif // TEXTURE2D_ARRAY_H
