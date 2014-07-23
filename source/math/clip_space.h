#ifndef _H_PUNK_MATH_CLIP_SPACE
#define _H_PUNK_MATH_CLIP_SPACE

#include <cstdint>
#include <vector>
#include <config.h>
#include "bounding_box.h"
#include "bounding_sphere.h"
#include "plane.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class TClipSpace
    {
    public:
        TClipSpace() {}

        TClipSpace(const TClipSpace &value) {}

        TClipSpace& operator = (const TClipSpace& value) {
            if (this == &value)
                return *this;
            this->m_planes = value.m_planes;
            return *this;
        }

        ~TClipSpace() {
        }

        void Add(const TPlane<T>& plane) {
            m_planes.push_back(plane);
        }

        std::uint32_t  GetSize() const {
            return (std::uint32_t)m_planes.size();
        }

        bool Empty() const {
            return m_planes.empty();
        }

        const TPlane<T>& operator [] (std::uint32_t index) const {
            return m_planes[index];
        }

        TPlane<T>& operator [] (std::uint32_t index) {
            return m_planes[index];
        }

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint>& point)
		{
			for (std::size_t i = 0; i != this->GetSize(); ++i)
			{
				auto r = (*space[i]).ClassifyPoint(point);
				if (r == Relation::BACK)
					return Relation::OUTSIDE;

			}
			return Relation::INSIDE;
		}


		//	Bounding box should be in clip space
		Relation ClassifyBoudingBox(const BoundingBox& bbox) const
		{
			if (bbox.GetR().Length() > 4 * bbox.GetS().Length() && bbox.GetR().Length() > 4 * bbox.GetT().Length())
			{
				auto q1 = bbox.GetCenter() - 0.5f * bbox.GetR();
				auto q2 = bbox.GetCenter() + 0.5f * bbox.GetR();

				for (auto i = 0u; i < GetSize(); ++i)
				{
					const auto plane = this->m_planes[i];
					const auto n = plane.GetNormal();
					T r_eff = 0.5f * (Abs(n.Dot(bbox.GetS())) + Abs(n.Dot(bbox.GetT())));

					T r1 = plane * q1;
					T r2 = plane * q2;

					if (r1 <= r_eff && r2 <= r_eff)
						return Relation::OUTSIDE;

					if (r1 >= r_eff && r2 >= r_eff)
						continue;

					T t = (r_eff + plane * q1) / (plane * (q1 - q2));
					auto q3 = q1 + t*(q2 - q1);

					if (r1 <= r_eff)
						q1 = q3;

					if (r2 <= r_eff)
						q2 = q3;
				}
				return Relation::INSIDE;
			}
			else
			{
				for (std::size_t i = 0, max_i = GetSize(); i < max_i; ++i)
				{
					auto plane = this->m_planes[i];
					const vec3 n = plane.GetNormal();
					T r_eff = 0.5f * (Abs(n.Dot(bbox.GetR())) + Abs(n.Dot(bbox.GetS())) + Abs(n.Dot(bbox.GetT())));

					T value = plane * bbox.GetCenter();
					if (value < -r_eff)
						return Relation::OUTSIDE;
				}
				return Relation::INSIDE;
			}
		}

		Relation ClassifyBoudingSphere(const TSphere<T>& sphere) const
		{
			const auto q = sphere.GetCenter();
			for (auto i = 0u; i < this->GetSize(); ++i)
			{
				auto plane = m_planes[i];
				T r = plane * q;
				if (r <= -sphere.GetRadius())
					return Relation::OUTSIDE;
			}
			return Relation::INSIDE;
		}

	private:
        std::vector<TPlane<T>> m_planes;
    };

    using ClipSpace = TClipSpace<float>;
}
PUNK_ENGINE_END

#endif
