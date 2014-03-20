#include "shadow_render_common.h"
#include <math/frustum.h>
#include <graphics/frame/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
    void FindZRange(const Math::FrustumCore& frustum, const Math::mat4& shadow_view, Frame* frame, Math::vec2& z_range)
    {
        z_range = Math::FrustumFindZRange(frustum, shadow_view);

        auto r = frame->FindZRange(shadow_view);
        if (z_range[0] > r[0])
            z_range[0] = r[0];

        if (z_range[1] < r[1])
            z_range[1] = r[1];
    }
}
PUNK_ENGINE_END
