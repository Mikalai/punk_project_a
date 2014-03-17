#ifndef TEXTURE_COMPARE_FUNC_H
#define TEXTURE_COMPARE_FUNC_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    enum class TextureCompareFunc { TextureLessEqual,
                                    TextureGreaterEqual,
                                    TextureLess,
                                    TextureGreater,
                                    TextureEqual,
                                    TextureNotEqual,
                                    TextureAlways,
                                    TextureNever };
}
PUNK_ENGINE_END

#endif // TEXTURE_COMPARE_FUNC_H
