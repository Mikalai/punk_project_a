#ifndef _H_PUNK_FRUSTUM
#define _H_PUNK_FRUSTUM

#include "config.h"
#include "vec3.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            class ClipSpace;
            class mat4;

            struct FrustumCore
            {
                float neard;
                float fard;
                float fov;
                float ratio;
                vec3  point[8];
            };

            PUNK_ENGINE_API const ClipSpace FrustumBuildClipSpaceFromPoint(const FrustumCore& f, const Math::vec3& p);
            PUNK_ENGINE_API const ClipSpace FrustumToClipSpace(const FrustumCore& f);
            PUNK_ENGINE_API const FrustumCore FrustumCreateFromProjectionMatrix(const Math::mat4& p);
            PUNK_ENGINE_API const vec2 FrustumFindZRange(const FrustumCore& f, const Math::mat4& view);
            PUNK_ENGINE_API void ProjectionMatrixToPlanes(const Math::mat4& p, Math::Plane (&planes)[6]);
            PUNK_ENGINE_API void FrustumTransform(FrustumCore& f, const vec3 &center, const vec3 &view_dir, const vec3 &_up);
            PUNK_ENGINE_API const Math::mat4 FrustumCreatePerspectiveProjectionMatrix(const Math::FrustumCore& f);
        }
    }
}

#endif
