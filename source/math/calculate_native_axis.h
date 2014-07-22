#ifndef _H_CALCULATE_NATIVE_AXIS
#define _H_CALCULATE_NATIVE_AXIS

#include <config.h>
#include <tuple>

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    void CalculateNativeAxis(const Tuple<T, 3, tagPoint>& points, std::uint32_t count, vec3& r, vec3& s, vec3& t)
    {
        //	find covariance matrix
        mat3 c = CreateCovarianceMatrix(points, count);

        //	find eigen values of the covariance matrix
        Math::vec3 eigen_values;
        EigenValues(c, eigen_values);

        //	find eigen vectors of the covariance matrix
        Math::vec3 eigen_vectors[3];
        EigenVectors(c, eigen_values, eigen_vectors);

        r = eigen_vectors[0];
        s = eigen_vectors[1];
        t = eigen_vectors[2];

        mat3 a;
        a.SetColumn(0, r);
        a.SetColumn(1, s);
        a.SetColumn(2, t);
    }

}
PUNK_ENGINE_END

#endif  // _H_CALCULATE_NATIVE_AXIS
