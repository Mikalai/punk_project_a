#ifndef _H_PUNK_MATH_BOUNDING_BOX
#define _H_PUNK_MATH_BOUNDING_BOX

#include <cstdint>
#include <config.h>
#include "tuple.h"
#include "plane.h"
#include "aabb.h"
#include "bounding_sphere.h"

PUNK_ENGINE_BEGIN
namespace Math {
	
    template<class T>
    class TBoundingBox {
	public:

        TBoundingBox()
        {}

        TBoundingBox(const TBoundingBox& value)
            : m_core(value.m_core) {}

        TBoundingBox& operator = (const TBoundingBox& value) {
            if (this != &value) {
                m_core = value.m_core;
            }
            return *this;
        }

        void Create(const std::vector<Tuple<T, 3, tagPoint>>& points) {

            //	check input data
            if (!points || count == 0)
                throw Error::NotEnoughData(0);

            //	find average of the vertices
            m_core.m_center_of_mass = Statistics::Average(points);

            CalculateNativeAxis(points, count, m_core.m_r, m_core.m_s, m_core.m_t);

            //	find plane distances
            float d[6];

            //	init distances with appropriate values
            const Tuple<T, 3, tagVector> v = points[0];
            d[0] = v.Dot(m_core.m_r);
            d[1] = v.Dot(m_core.m_r);

            d[2] = v.Dot(m_core.m_s);
            d[3] = v.Dot(m_core.m_s);

            d[4] = v.Dot(m_core.m_t);
            d[5] = v.Dot(m_core.m_t);

            for (auto i = 0u; i < count; ++i)
            {
                float r = m_core.m_r.Dot(v);
                if (d[0] > r)
                    d[0] = r;
                if (d[1] < r)
                    d[1] = r;

                float s = m_core.m_s.Dot(v);
                if (d[2] > s)
                    d[2] = s;
                if (d[3] < s)
                    d[3] = s;

                float t = m_core.m_t.Dot(v);
                if (d[4] > t)
                    d[4] = t;
                if (d[5] < t)
                    d[5] = t;
            }

            //	find natural planes
            m_core.m_plane[0].Set(m_core.m_r, -d[0]);
            m_core.m_plane[1].Set(-m_core.m_r, d[1]);
            m_core.m_plane[2].Set(m_core.m_s, -d[2]);
            m_core.m_plane[3].Set(-m_core.m_s, d[3]);
            m_core.m_plane[4].Set(m_core.m_t, -d[4]);
            m_core.m_plane[5].Set(-m_core.m_t, d[5]);

            //	find bbox center
            {
                float a = (d[0] + d[1]) / 2.0f;
                float b = (d[2] + d[3]) / 2.0f;
                float c = (d[4] + d[5]) / 2.0f;

                m_core.m_center = a*m_core.m_r + b*m_core.m_s + c*m_core.m_t;

                m_core.m_r *= (d[1] - d[0]);
                m_core.m_s *= (d[3] - d[2]);
                m_core.m_t *= (d[5] - d[4]);

                m_core.m_min_corner = m_core.m_center - m_core.m_r * 0.5f - m_core.m_s * 0.5f - m_core.m_t * 0.5f;
            }
        }

        const BoundingSphere ToBoundingSphere()
        {
            Tuple<T, 3, tagVector> p[] {m_core.m_min_corner, m_core.m_min_corner + m_core.m_r + m_core.m_s + m_core.m_t, m_core.m_min_corner + m_core.m_r, m_core.m_min_corner + m_core.m_s};
            BoundingSphere s;
            s.Create(p, sizeof(p) / sizeof(p[0]));
            return s;
        }      

        const Tuple<T, 3, tagVector>& GetR() const {
            return m_core.m_r;
        }

        const Tuple<T, 3, tagVector>& GetS() const {
            return m_core.m_s;
        }

        const Tuple<T, 3, tagVector>& GetT() const {
            return m_core.m_t;
        }

        const Tuple<T, 3, tagVector>& GetCenter() const {
            return m_core.m_center;
        }

        const Tuple<T, 3, tagVector>& GetMassCenter() const {
            return m_core.m_center_of_mass;
        }

        const Tuple<T, 3, tagVector>& GetMinCorner() const {
            return m_core.m_min_corner;
        }

        const Plane& GetPlane(int index) const {
            return m_core.m_plane[index];
        }

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint>& point)
		{
			for (int i = 0; i < 6; ++i)
			{
				const Plane p = GetPlane(i);
				Relation relation = ClassifyPoint(point, p);
				if (relation == Relation::BACK)
					return Relation::OUTSIDE;
			}
			return Relation::INSIDE;
		}

		Relation CrossLine(const Line3D& line, Tuple<T, 3, tagVector>& p)
		{
			mat4 t;
			t.SetColumn(0, vec4(this->GetR(), 0));
			t.SetColumn(1, vec4(this->GetS(), 0));
			t.SetColumn(2, vec4(this->GetT(), 0));
			t.SetColumn(3, vec4(this->GetMinCorner().X(), this->GetMinCorner().Y(), this->GetMinCorner().Z(), 1));

			auto l = t.Inversed() * line;

			TAxisAlignedBox<T> aabb;
			aabb.Set(Tuple<T, 3, tagVector>(0, 0, 0), Tuple<T, 3, tagVector>(this->GetR().Length(), this->GetS().Length(), this->GetT().Length()));
			T tmin;
			if (Relation::NOT_INTERSECT == CrossLineAxisAlignedBox(l, aabb, tmin, p))
				return Relation::NOT_INTERSECT;
			p = t * p;
			return Relation::INTERSECT;
		}

	private:

		struct Core {
			//	natural center
			Tuple<T, 3, tagVector> m_center_of_mass;
			//	bbox center
			Tuple<T, 3, tagVector> m_center;
			Tuple<T, 3, tagVector> m_min_corner;
			//	natural axes
			Tuple<T, 3, tagVector> m_r;
			Tuple<T, 3, tagVector> m_s;
			Tuple<T, 3, tagVector> m_t;
			//	natural planes of the bbox
			Plane m_plane[6];
		};

		Core m_core;


        friend const TBoundingBox<T> operator * (const Matrix<T, 4, 4>& m, const TBoundingBox<T>& bbox);
	};

    template<class T>
    const TBoundingBox<T> operator * (const Matrix<T, 4, 4>& m, const TBoundingBox<T>& bbox)
    {
        TBoundingBox<T> res;
        Matrix<T, 4, 4> plane_matrix = m.Inversed().Transposed();
        Matrix<T, 3, 3> normal_matrix = plane_matrix.RotationPart();

        res.m_core.m_center_of_mass = m * this->m_core.m_center_of_mass;
        res.m_core.m_center = m * this->m_core.m_center;
        res.m_core.m_r = normal_matrix * this->m_core.m_r;
        res.m_core.m_s = normal_matrix * this->m_core.m_s;
        res.m_core.m_t = normal_matrix * this->m_core.m_t;

        for (int i = 0; i < 6; ++i)
        {
            res.m_core.m_plane[i] = plane_matrix * this->m_core.m_plane[i];
        }

        return res;
    }

    using BoundingBox = TBoundingBox<float>;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_BOUNDING_BOX
