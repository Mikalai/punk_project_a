#ifndef _H_PUNK_MATH_BOUNDING_SPHERE
#define _H_PUNK_MATH_BOUNDING_SPHERE

#include <cstdint>
#include <config.h>
#include "sphere.h"
#include "calculate_native_axis.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class TBoundingSphere : public TSphere<T> {
    public:
        TBoundingSphere() {}
        TBoundingSphere(const TSphere<T>& s) 
			: TSphere<T>(s) {}

        void Create(const std::vector<Tuple<T, 3, tagPoint>>& points) {
            if (points.empty())
                throw Error::NotEnoughData(0);

            Tuple<T, 3, tagVector> r, s, t;
            CalculateNativeAxis(points, r, s, t);

            auto min_p = points[0];
            T min_value = r.Dot(min_p.GetRadiusVector());
            auto max_p = min_p;
            T max_value = r.Dot(max_p.GetRadiusVector());

            for (auto i = 0u; i < points.size(); ++i)
            {
                T value = r.Dot(points[i].GetRadiusVector());
                if (min_value > value)
                {
                    min_p = points[i];
                    min_value = value;
                }

                if (max_value < value)
                {
                    max_p = points[i];
                    max_value = value;
                }
            }

            const auto q = (min_p + max_p) / 2.0f;
            T radius = (min_p - q).Length();

            SetCenter(q);
            SetRadius(radius);
        }

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint>& point) {
			T sqr_dst = (point - this->GetCenter()).SquareLength();
			T r = this->GetRadius();
			if (sqr_dst > r*r)
				return Relation::OUTSIDE;
			return Relation::INSIDE;
		}
    };

    template<class T>
    const TBoundingSphere<T> operator * (const Matrix<T, 4, 4>& m, const TBoundingSphere<T>& bsphere) {
        TBoundingSphere<T> res;
        res.SetCenter(m * bsphere.GetCenter());
        res.SetRadius(bsphere.GetRadius());
        return res;
    }

	using BoundingSphere = TBoundingSphere < float > ;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_BOUNDING_SPHERE
