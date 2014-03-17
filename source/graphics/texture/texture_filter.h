#ifndef TEXTURE_FILTER_H
#define TEXTURE_FILTER_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    enum class TextureFilter { Nearest,
                               Linear,
                               NearestMipmapNearest,
                               LinearMipmapNearest,
                               NearestMipmapLinear,
                               LinearMipmapLinear
                             };
}
PUNK_ENGINE_END

#endif // TEXTURE_FILTER_H
