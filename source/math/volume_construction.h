#ifndef VOLUME_CONSTRUCTION_H
#define VOLUME_CONSTRUCTION_H

#include <cstdint>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            class vec3;
            class mat3;

            PUNK_ENGINE_API const vec3 CalculateAverage(const vec3* points, std::uint32_t count);
            PUNK_ENGINE_API const mat3 CreateCovarianceMatrix(const vec3* points, std::uint32_t count);
            PUNK_ENGINE_API void DiagonalizeMatrix(const mat3& m, mat3& res);
            PUNK_ENGINE_API void EigenValues(const mat3& m, vec3& res);
            PUNK_ENGINE_API void EigenVectors(const mat3& m, const vec3& value, vec3 res[3]);
            PUNK_ENGINE_API void SymmetricEigenSystem(const mat3& m, vec3& value, mat3& r);
            //	used to find native axis of the point set
            PUNK_ENGINE_API void CalculateNativeAxis(const vec3* points, std::uint32_t count, vec3& r, vec3& s, vec3& t);

        }
    }
}

#endif // VOLUME_CONSTRUCTION_H
