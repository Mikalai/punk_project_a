#ifndef SHADOW_RENDER_COMMON_H
#define SHADOW_RENDER_COMMON_H

namespace Math
{
    class FrustumCore;
    class mat4;
    class vec2;
}

namespace Graphics
{
    class IFrame;

    void FindZRange(const Math::FrustumCore& frustum, const Math::mat4& shadow_view, IFrame* frame, Math::vec2& z_range);
}

#endif // SHADOW_RENDER_COMMON_H
