#ifndef _H_PUNK_MATH_ELLIPSOID
#define _H_PUNK_MATH_ELLIPSOID

#include "config.h"
#include "tuple.h"
#include "line.h"
#include "relations.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class TEllipsoid
    {
    public:
        TEllipsoid(T rx, T ry, T rz)
            : m_rx(rx), m_ry(ry), m_rz(rz) {}

        T GetRadiusX() const {
            return m_rx;
        }

        T GetRadiusY() const {
            return m_ry;
        }

        T GetRadiusZ() const {
            return m_rz;
        }

        void SetRadiusX(T value) {
            m_rx = value;
        }

        void SetRadiusY(T value) {
            m_ry = value;
        }

        void SetRadiusZ(T value) {
            m_rz = value;
                                     }

        void SetDimension(T rx, T ry, T rz) {
            (m_rx = rx, m_ry = ry, m_rz = rz);
        }

        void SetCenter(const Tuple<T, 3, tagPoint>& value) {
            m_center = value;
        }

        const Tuple<T, 3, tagPoint>& GetCenter() const {
            return m_center;
        }

		Relation CrossLine(const Line<T, 3>& line, T& t1, T& t2)
		{
			T m = this->GetRadiusX() / this->GetRadiusY();
			T n = this->GetRadiusX() / this->GetRadiusZ();
			T r = this->GetRadiusX();

			const vec3 s = line.GetOrigin() - this->GetCenter();
			const vec3 v = line.GetDestination() - line.GetOrigin();

			T a = v[0] * v[0] + m*m*v[1] * v[1] + n*n*v[2] * v[2];
			T b = 2 * (s[0] * v[0] + m*m*s[1] * v[1] + n*n*s[2] * v[2]);
			T c = s[0] * s[0] + m*m*s[1] * s[1] + n*n*s[2] * s[2] - r*r;

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

		Relation CrossLine(const Line<T, 3>& line, vec3& p1, vec3& p2)
		{
			T t1, t2;
			Relation res = this->CrossLineEllipsoid(line, t1, t2);
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


    private:
        T m_rx;
        T m_ry;
        T m_rz;
        Tuple<T, 3, tagPoint> m_center;
    };

    using Ellipsoid = TEllipsoid<float>;
}
PUNK_ENGINE_END

#endif	//	_H_LPW_ELLIPSOID
