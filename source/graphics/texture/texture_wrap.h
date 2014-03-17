#ifndef TEXTURE_WRAP_H
#define TEXTURE_WRAP_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    enum class TextureWrapDirection { S, T, R };
    enum class TextureWrapMode { ClampToEdge, ClampToBorder, MirroredRepeat, Repeat, MirrorClampToEdge };
}
PUNK_ENGINE_END

#endif // TEXTURE_WRAP_H
