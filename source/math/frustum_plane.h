#ifndef H_PUNK_MATH_FRUSTUM_PLANE_H
#define H_PUNK_MATH_FRUSTUM_PLANE_H

#include <cstdint>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Core {
            class String;
        }

        namespace Math {

            enum class FrustumPlane : uint8_t {
                Top = 0,
                Bottom = 1,
                Left = 2,
                Right = 3,
                Far = 4,
                Near = 5
            };

            PUNK_ENGINE_API bool IsAdjacent(FrustumPlane a, FrustumPlane b);
            PUNK_ENGINE_API const Core::String AsString(const FrustumPlane& value);

            constexpr int GetIndex(const FrustumPlane p)
            {
                return (int)p;
            }
        }
    }
}

#endif // FRUSTUM_PLANE_H
