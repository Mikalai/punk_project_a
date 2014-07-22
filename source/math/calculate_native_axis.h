#ifndef _H_CALCULATE_NATIVE_AXIS
#define _H_CALCULATE_NATIVE_AXIS

#include <config.h>
#include "tuple.h"
#include "matrix.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    void CalculateNativeAxis(
		const std::vector<Tuple<T, 3, tagPoint>>& points, 
		Tuple<T, 3, tagVector>& r,
		Tuple<T, 3, tagVector>& s, 
		Tuple<T, 3, tagVector>& t)
    {
        //	find covariance matrix
		auto c = Matrix<T, 3, 3>::CreateCovarianceMatrix(points);

        //	find eigen values of the covariance matrix
        auto eigen_values = c.EigenValues();

        //	find eigen vectors of the covariance matrix
        Tuple<T, 3, tagVector> eigen_vectors[3];
		c.EigenVectors(eigen_values, eigen_vectors);

        r = eigen_vectors[0];
        s = eigen_vectors[1];
        t = eigen_vectors[2];        
    }

}
PUNK_ENGINE_END

#endif  // _H_CALCULATE_NATIVE_AXIS
