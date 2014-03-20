#ifndef SHADOW_RENDER_COMMON_H
#define SHADOW_RENDER_COMMON_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {
    class FrustumCore;
    class mat4;
    class vec2;
}

namespace Graphics {
    class Frame;
    void FindZRange(const Math::FrustumCore& frustum, const Math::mat4& shadow_view, Frame* frame, Math::vec2& z_range);
}
PUNK_ENGINE_END

#endif // SHADOW_RENDER_COMMON_H
