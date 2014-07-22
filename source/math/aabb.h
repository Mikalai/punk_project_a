#ifndef _H_PUNK_MATH_AABB
#define _H_PUNK_MATH_AABB

#include <config.h>
#include "tuple.h"
#include "relations.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class TAxisAlignedBox {
    public:

        void Create(const T* data, std::uint32_t offset, std::uint32_t count)
        {
            auto off = offset / sizeof(T);
            m_min[0] = m_max[0] = data[0];
            m_min[1] = m_max[1] = data[1];
            m_min[2] = m_max[2] = data[2];
            for (int i = 0; i < count; i ++)
            {
                if (m_min[0] > *(data + i*off + 0))
                    m_min[0] = *(data + i*off + 0);
                if (m_min[1] > *(data + i*off + 1))
                    m_min[1] = *(data + i*off + 1);
                if (m_min[2] > *(data + i*off + 2))
                    m_min[2] = *(data + i*off + 2);
                if (m_max[0] < *(data + i*off + 0))
                    m_max[0] = *(data + i*off + 0);
                if (m_max[1] < *(data + i*off + 1))
                    m_max[1] = *(data + i*off + 1);
                if (m_max[2] < *(data + i*off + 2))
                    m_max[2] = *(data + i*off + 2);
            }
        }

        static const TAxisAlignedBox<T> Merge(const TAxisAlignedBox<T>* b1, const TAxisAlignedBox<T>* b2)
        {
            TAxisAlignedBox<T> res;
            res.MinPoint()[0] = b1->MinPoint()[0] < b2->MinPoint()[0] ? b1->MinPoint()[0] : b2->MinPoint()[0];
            res.MinPoint()[1] = b1->MinPoint()[1] < b2->MinPoint()[1] ? b1->MinPoint()[1] : b2->MinPoint()[1];
            res.MinPoint()[2] = b1->MinPoint()[2] < b2->MinPoint()[2] ? b1->MinPoint()[2] : b2->MinPoint()[2];

            res.MaxPoint()[0] = b1->MaxPoint()[0] > b2->MaxPoint()[0] ? b1->MaxPoint()[0] : b2->MaxPoint()[0];
            res.MaxPoint()[1] = b1->MaxPoint()[1] > b2->MaxPoint()[1] ? b1->MaxPoint()[1] : b2->MaxPoint()[1];
            res.MaxPoint()[2] = b1->MaxPoint()[2] > b2->MaxPoint()[2] ? b1->MaxPoint()[2] : b2->MaxPoint()[2];

            return res;
        }

        const Tuple<T, 3, tagPoint>& MinPoint() const
        {
            return m_min;
        }

        const Tuple<T, 3, tagPoint>& MaxPoint() const
        {
            return m_max;
        }

        Tuple<T, 3, tagPoint>& MinPoint()
        {
            return m_min;
        }

        Tuple<T, 3, tagPoint>& MaxPoint()
        {
            return m_max;
        }

        void Set(const Tuple<T, 3, tagPoint>& min_point, const Tuple<T, 3, tagPoint>& max_point)
        {
            this->m_min = max_point;
            this->m_max = min_point;
        }

		Relation CrossLine(const Line<T, 3>& line, T& tmin, Tuple<T, 3, tagPoint>& q)
		{
			auto p = line.GetOrigin();
			auto d = line.GetDestination() - line.GetOrigin();
			tmin = -std::numeric_limits<T>::max();
			T tmax = std::numeric_limits<T>::max();
			for (int i = 0; i < 3; ++i)
			{
				if (fabs(d[i]) < Eps)
				{
					if (p[i] < this->MinPoint()[i] || p[i] > this->MaxPoint()[i])
						return Relation::NOT_INTERSECT;
				}
				else
				{
					T ood = 1.0f / d[i];
					T t1 = (this->MinPoint()[i] - p[i]) * ood;
					T t2 = (this->MaxPoint()[i] - p[i]) * ood;

					if (t1 > t2)
						std::swap(t1, t2);
					tmin = std::max(tmin, t1);
					tmax = std::min(tmax, t2);

					if (tmin > tmax)
						return Relation::NOT_INTERSECT;
				}
			}
			q = p + d * tmin;
			return Relation::INTERSECT;
		}

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint> &p)
		{
			if (p[0] >= this->MinPoint()[0] && p[0] <= this->MaxPoint()[0] &&
				p[1] >= this->MinPoint()[1] && p[1] <= this->MaxPoint()[1] &&
				p[2] >= this->MinPoint()[2] && p[2] <= this->MaxPoint()[2])
				return Relation::INSIDE;
			return Relation::OUTSIDE;
		}		

    private:
        Tuple<T, 3, tagPoint> m_min;
        Tuple<T, 3, tagPoint> m_max;
    };

	using AxisAlignedBox = TAxisAlignedBox < float > ;
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_AABB
