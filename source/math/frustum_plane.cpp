#include <string/string.h>
#include "frustum_plane.h"

namespace Punk {
    namespace Engine {
        namespace Math {

#ifdef USE_QT
            const QString AsString(const FrustumPlane& value)
#else
            const Core::String AsString(const FrustumPlane& value)
#endif
            {
                switch(value)
                {
                case FrustumPlane::Bottom:
                    return "Bottom";
                case FrustumPlane::Far:
                    return "Far";
                case FrustumPlane::Left:
                    return "Left";
                case FrustumPlane::Near:
                    return "Near";
                case FrustumPlane::Right:
                    return "Right";
                case FrustumPlane::Top:
                    return "Top";
                default:
                    return "Error";
                }
            }

            bool IsAdjacent(FrustumPlane a, FrustumPlane b)
            {
                switch (a)
                {
                case FrustumPlane::Top:
                    if (b == FrustumPlane::Bottom)
                        return false;
                    else
                        return true;
                case FrustumPlane::Far:
                    if (b == FrustumPlane::Near)
                        return false;
                    else
                        return true;
                case FrustumPlane::Left:
                    if (b == FrustumPlane::Right)
                        return false;
                    else
                        return true;
                case FrustumPlane::Near:
                    if (b == FrustumPlane::Far)
                        return false;
                    else
                        return true;
                case FrustumPlane::Right:
                    if (b == FrustumPlane::Left)
                        return false;
                    else
                        return true;
                case FrustumPlane::Bottom:
                    if (b == FrustumPlane::Top)
                        return false;
                    else
                        return true;
                }
                return false;
            }
        }
    }
}
