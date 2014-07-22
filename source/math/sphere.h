#ifndef _H_PUNK_MATH_SPHERE
#define _H_PUNK_MATH_SPHERE

#include <config.h>
#include "matrix.h"
#include "tuple.h"
#include "line.h"
#include "root_find.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class TSphere
    {
    public:
        TSphere()
            : m_center{}
            , m_radius{0}
        {}

        TSphere(const Tuple<T, 3, tagPoint>& center, T radius)
            : m_center{center}
            , m_radius{radius}
        {}

        void SetCenter(const Tuple<T, 3, tagPoint>& center) {
            m_center = center;
        }

        void SetRadius(T radius) {
            m_radius = radius;
        }

        void Set(const Tuple<T, 3, tagPoint>& center, T radius) {
            m_center = center;
            m_radius = radius;
        }

        T GetRadius() const {
            return m_radius;
        }

        const Tuple<T, 3, tagPoint>& GetCenter() const {
            return m_center;
        }

		Relation CrossLine(const Line<T, 3>& line, T& t1, T& t2)
		{
			const auto org = line.GetOrigin() - this->GetCenter();
			const auto dir = line.GetDestination() - line.GetOrigin();
			T a = dir.SquareLength();
			T b = 2 * org.Dot(dir);
			T c = org.SquareLength() - this->GetRadius()*this->GetRadius();

			T in[] = { c, b, a };
			T out[2];
			RootFindResult res = SolveQuadric(in, out);
			if (res == RootFindResult::RESULT_NO_SOLUTION)
				return Relation::NOT_INTERSECT;
			if (res == RootFindResult::RESULT_ONE_SOLUTION)
			{
				t1 = out[0];
				return Relation::INTERSECT;
			}
			else if (res == RootFindResult::RESULT_TWO_SOLUTIONS)
			{
				t1 = out[0];
				t2 = out[1];
				return Relation::INTERSECT_2;
			}
			return Relation::NOT_INTERSECT;
		}

		Relation CrossLine(const Line<T, 3>& line, Tuple<T, 3, tagPoint>& p1, Tuple<T, 3, tagPoint>& p2)
		{
			T t1, t2;
			Relation res = this->CrossLine(line, t1, t2);
			if (res == Relation::NOT_INTERSECT)
				return Relation::NOT_INTERSECT;
			else if (res == Relation::INTERSECT_1)
			{
				p1 = line.PointAt(t1);
				return Relation::INTERSECT_1;
			}
			else if (res == Relation::INTERSECT_2)
			{
				p1 = line.PointAt(t1);
				p2 = line.PointAt(t2);
				return Relation::INTERSECT_2;
			}
			return Relation::NOT_INTERSECT;
		}

		Relation CrossSphere(const TSphere<T>& b)
		{
			T dst = this->GetRadius() + b.GetRadius();
			T sqr_dst = dst * dst;
			T cur_dst = (this->GetCenter() - b.GetCenter()).SquareLength();
			if (cur_dst < sqr_dst)
				return Relation::INTERSECT;
			return Relation::NOT_INTERSECT;
		}

    private:
        Tuple<T, 3, tagPoint> m_center;
        T m_radius;

        friend const TSphere<T> operator * (const Matrix<T, 4, 4>& m, const TSphere<T>& s);
    };

    template<class T>
    const TSphere<T> operator * (const Matrix<T, 4, 4>& m, const TSphere<T>& s)
    {
        TSphere<T> res;
        res.m_center = m * s.GetCenter();
        //	consider that transform do not effect the radius
        res.m_radius = s.GetRadius();
        return res;
    }

    template<class T>
    const TSphere<T> operator + (const TSphere<T>& a, const TSphere<T>& b)
    {
        T d = (this->GetCenter() - b.GetCenter()).Length();
        if (d + this->GetRadius() <= b.GetRadius())
            return b;
        if (d + b.GetRadius() <= this->GetRadius())
            return a;

        TSphere<T> res;
        T r = T{0.5} * (d + this->GetRadius() + b.GetRadius());
        res.SetRadius(r);
        res.SetCenter(this->GetCenter() + (r - this->GetRadius()) / d * (b.GetCenter() - this->GetCenter()));
        return res;
    }

	using Sphere = TSphere < float > ;

}
PUNK_ENGINE_END

#endif
