#ifndef _H_PUNK_RECOUNT_H
#define _H_PUNK_RECOUNT_H

#include "forward.h"
#include "spherical.h"

PUNK_ENGINE_BEGIN
namespace Math
{
    class Recount
    {
    public:
        static const vec3 SphericalToCartesian(float phi, float theta);
        static const vec3 SphericalToCartesian(float phi, float theta, float r);
        static const vec3 SphericalToCartesian(const SphericalCoordinate& p);
        static const SphericalCoordinate CartesianToSpherical(float x, float y, float z);
        static const SphericalCoordinate CartesianToSpherical(const vec3& value);
        static float DegToRad(float value);
        static float RadToDeg(float value);
    };
}
PUNK_ENGINE_END

#endif // RECOUNT_H
