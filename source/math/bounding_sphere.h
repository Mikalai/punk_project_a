#ifndef _H_PUNK_MATH_BOUNDING_SPHERE
#define _H_PUNK_MATH_BOUNDING_SPHERE

#include <cstdint>
#include <config.h>
#include "sphere.h"

PUNK_ENGINE_BEGIN
namespace Math {
    class PUNK_ENGINE_API BoundingSphere : public Sphere
    {
    public:
        BoundingSphere() {}
        BoundingSphere(const Sphere& s) : Sphere(s) {}
        void Create(const vec3* points, std::uint32_t count);
    };

    PUNK_ENGINE_API const BoundingSphere operator * (const mat4& m, const BoundingSphere& bsphere);
}
PUNK_ENGINE_END
#endif	//	_H_PUNK_MATH_BOUNDING_SPHERE
