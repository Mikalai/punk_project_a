#ifndef TEXTURE_CONVER_H
#define TEXTURE_CONVER_H

#include <graphics/opengl/module.h>

PUNK_ENGINE_BEGIN
namespace ImageModule{
    enum class ImageFormat : unsigned;
    enum class DataType : unsigned;
}

namespace Graphics {
    enum class TextureFilter;
    enum class TextureWrapMode;
    enum class TextureWrapDirection;
    enum class TextureCompareFunc;
    enum class TextureCompareMode;

    namespace OpenGL {
        GLenum Convert(const TextureFilter& value);
        GLenum Convert(const TextureWrapMode& value);
        GLenum Convert(const TextureWrapDirection& value);
        GLenum Convert(const TextureCompareFunc& value);
        GLenum Convert(const TextureCompareMode& value);
        GLenum Convert(const ImageModule::ImageFormat& format);
        GLenum Convert(const ImageModule::DataType& value);
        size_t PixelSize(const ImageModule::ImageFormat& value);
    }
}
PUNK_ENGINE_END

#endif // TEXTURE_CONVER_H
