#ifndef _H_CREATE_COVARIANCE_MATRIX
#define _H_CREATE_COVARIANCE_MATRIX

#include <config.h>
#include "matrix.h"
#include "tuple.h"
#include "calculate_average.h"

PUNK_ENGINE_BEGIN
namespace Math {

    const Matrix<T, 3, 3> CreateCovarianceMatrix(const Tuple<T, 3, tagPoint>* points, std::uint32_t count)
    {
        //	find average of the vertices
        auto center = CalculateAverage(points, count);

        //	find covariance matrix
        Matrix<T, 3, 3> res;
        res.Zerofy();

        for (auto i = 0u; i < count; ++i)
        {
            res += MultTransposed((points[i] - center), (points[i] - center));
        }

        res /= (float)count;

        return res;
    }
}
PUNK_ENGINE_END

#endif  //  _H_CREATE_COVARIANCE_MATRIX
