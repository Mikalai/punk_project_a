#ifndef SHADOW_MODEL_H
#define SHADOW_MODEL_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Graphics
{
    enum class ShadowModel { ShadowMapSimple, ShadowMapCascade };

    extern PUNK_ENGINE_API const Core::String AsString(ShadowModel value);
}
PUNK_ENGINE_END

#endif // SHADOW_MODEL_H
