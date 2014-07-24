#ifndef _H_PUNK_MATH_PORTAL
#define _H_PUNK_MATH_PORTAL

#include <cstdint>
#include <vector>
#include <config.h>
#include "tuple.h"
#include "matrix.h"
#include "plane.h"
#include "clip_space.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class TPortal {
    public:

        bool SetPoints(const Tuple<T, 3, tagPoint>* points, std::uint32_t count)
        {
            if (count < 3)
                throw Error::NotEnoughData(0);

            m_points.resize(count);
            for (auto i = 0u; i < count; ++i)
                m_points[i] = points[i];

            const Tuple<T, 3, tagPoint>& p0 = m_points[0];
            const Tuple<T, 3, tagPoint>& p1 = m_points[1];
            const Tuple<T, 3, tagPoint>& p2 = m_points[2];

            m_plane.Set(p0, p1, p2);

            return true;
        }
        const Tuple<T, 3, tagPoint> GetNormal() const {
            return m_plane.GetNormal();
        }

        float GetDistance() const {
            return m_plane.GetDistance();
        }

        std::uint32_t GetSize() const {
            return (std::uint32_t)m_points.size();
        }

        void SetSize(std::uint32_t value) {
            m_points.resize(value);
        }

        Tuple<T, 3, tagPoint>& operator [] (std::uint32_t index) {
            return m_points[index];
        }

        const Tuple<T, 3, tagPoint>& operator [] (std::uint32_t index) const {
            return m_points[index];
        }

		//	clipping should be performed in camera space
		Relation Clip(const TClipSpace<T>& clipper, TPortal<T>& clipped_portal, TClipSpace<T>& reduced_frustum)
		{
			//	check negative side of the portal
			if (this->GetDistance() < 0)
			{
				//out_message() << "PORTAL NOT VISIBLE" << std::endl;
				return Relation::NOT_VISIBLE;
			}

			bool partial_visible = false;
			TPortal<T> temp(portal);
			FrustumPlane p = (FrustumPlane)0;
			for (std::size_t j = 0u, max_j = clipper.GetSize(); j < max_j; ++j)
			{
				auto plane = clipper[j];
				std::vector<int> in_points; in_points.reserve(this->GetSize());
				std::vector<int> out_points; out_points.reserve(this->GetSize());
				std::vector<int> on_points; on_points.reserve(this->GetSize());
				std::vector<Relation> flags; flags.reserve(this->GetSize());

				for (int i = 0; i < (int)temp.GetSize(); ++i)
				{
					const vec3& point = temp[i];
					auto dst = clipper[j] * point;

					if (dst < -0.001)	//	back
					{
						out_points.push_back(i);
						flags.push_back(Relation::BACK);
					}
					else if (dst > 0)
					{
						in_points.push_back(i);
						flags.push_back(Relation::FRONT);
					}
					else
					{
						on_points.push_back(i);
						flags.push_back(Relation::ON);
					}
				}

				//	if no points inside than portal is invisible
				if (in_points.empty() && !out_points.empty())
				{
					//	out_message() << "PORTAL NOT VISIBLE" << std::endl;
					return Relation::NOT_VISIBLE;
				}

				//	if no points outside than portal is visible
				if (out_points.empty())
				{
					//	out_message() << "PORTAL VISIBLE" << std::endl;
					continue;
				}

				// otherwise portal should be clipped
				//	out_message() << "PORTAL PARTIALLY VISIBLE" << std::endl;
				int mod = temp.GetSize();
				std::vector<vec3> new_points;
				for (int i = 0; i < (int)temp.GetSize(); ++i)
				{
					if (flags[i] == Relation::FRONT || flags[i] == Relation::ON)
						new_points.push_back(temp[i]);

					if (flags[i] == Relation::FRONT && flags[(i + 1) % mod] == Relation::BACK)
					{
						vec3 new_point;
						CrossLinePlane(Line3D(temp[i], temp[(i + 1) % mod]), plane, new_point);
						new_points.push_back(new_point);
					}

					if (flags[i] == Relation::BACK && flags[(i + 1) % mod] == Relation::FRONT)
					{
						vec3 new_point;
						CrossLinePlane(Line3D(temp[i], temp[(i + 1) % mod]), plane, new_point);
						new_points.push_back(new_point);
					}
				}

				p = (FrustumPlane)((int)p + 1);
				temp.SetPoints(&new_points[0], (std::uint32_t)new_points.size());
			}

			//	create reduced frustum
			int mod = (int)temp.GetSize();
			for (int i = 0; i < (int)temp.GetSize(); ++i)
			{
				const vec3 p0 = temp[i];
				const vec3 p1 = temp[(i + 1) % mod];

				const vec3 normal = p0.Cross(p1).Normalized();
				Plane p(normal, 0);

				reduced_frustum.Add(p);
			}

			if (partial_visible)
				return Relation::PARTIALLY_VISIBLE;

			clipped_portal = temp;  //  TODO: Check this statement

			return Relation::VISIBLE;
		}

    private:
        std::vector<Tuple<T, 3, tagPoint>> m_points;
        TPlane<T> m_plane;

        friend const TPortal<T> operator * (const Matrix<T, 4, 4>& m, const TPortal<T>& p);
    };

    //	transforms portal to other space
    template<class T>
    const TPortal<T> operator * (const Matrix<T, 4, 4>& m, const TPortal<T>& p)
    {
        TPortal<T> result;
        result.SetSize(p.GetSize());
        for (auto i = 0u; i < p.GetSize(); ++i) {
            result[i] = m*p[i];
        }
        return result;
    }

    using Portal = TPortal<float>;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_PORTAL
