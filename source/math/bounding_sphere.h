#ifndef _H_PUNK_MATH_BOUNDING_SPHERE
#define _H_PUNK_MATH_BOUNDING_SPHERE

#include <cstdint>
#include "sphere.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            class BoundingSphere : public Sphere
            {
            public:
                BoundingSphere() {}
                BoundingSphere(const Sphere& s) : Sphere(s) {}
                void Create(const vec3* points, std::uint32_t count);
            };

            PUNK_ENGINE_API const BoundingSphere operator * (const mat4& m, const BoundingSphere& bsphere);
        }
    }
}
#endif	//	_H_PUNK_MATH_BOUNDING_SPHERE
