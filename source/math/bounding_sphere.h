#ifndef _H_PUNK_MATH_BOUNDING_SPHERE
#define _H_PUNK_MATH_BOUNDING_SPHERE

#include <cstdint>
#include <config.h>
#include "sphere.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class TBoundingSphere : public TSphere<T> {
    public:
        TBoundingSphere() {}
        TBoundingSphere(const TSphere<T>& s) 
			: TSphere<T>(s) {}

        void Create(const std::vector<Tuple<T, 3, tagPoint>>& points) {
            if (count == 0 || points == nullptr)
                throw Error::NotEnoughData(0);

            vec3 r, s, t;
            CalculateNativeAxis(points, count, r, s, t);

            vec3 min_p = points[0];
            float min_value = r.Dot(min_p);
            vec3 max_p = min_p;
            float max_value = r.Dot(max_p);

            for (auto i = 0u; i < count; ++i)
            {
                float value = r.Dot(points[i]);
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

            const vec3 q = (min_p + max_p) / 2.0f;
            float radius = (min_p - q).Length();

            SetCenter(q);
            SetRadius(radius);
        }

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint>& point) {
			float sqr_dst = (point - this->GetCenter()).SquareLength();
			float r = this->GetRadius();
			if (sqr_dst > r*r)
				return Relation::OUTSIDE;
			return Relation::INSIDE;
		}
    };

    template<class T>
    const TBoundingSphere<T> operator * (const Matrix<T, 4, 4>& m, const TBoundingSphere<T>& bsphere) {
        TBoundingSphere res;
        res.SetCenter(m * bsphere.GetCenter());
        res.SetRadius(bsphere.GetRadius());
        return res;
    }

	using BoundingSphere = TBoundingSphere < float > ;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_BOUNDING_SPHERE
