#ifndef TEXTURE_COMPARE_MODE_H
#define TEXTURE_COMPARE_MODE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    enum class TextureCompareMode {
        TextureNone,
        CompareRefToTexture };
}
PUNK_ENGINE_END

#endif // TEXTURE_COMPARE_MODE_H
