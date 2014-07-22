/*
    File: plane.h
    Author: Mikalaj Abramau
    Desc: Description of geometry 3d plane
*/

#ifndef _H_PUNK_PLANE
#define _H_PUNK_PLANE

#include <config.h>
#include "tuple.h"
#include "line.h"
#include "matrix.h"

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class TPlane {
    public:

        TPlane() : m_plane{0, 0, 0, 0} {}

        TPlane(const TPlane<T>& plane) {
            if (this != &plane) {
                m_plane = plane.m_plane;
            }
        }

        TPlane(const Tuple<T, 3, tagPoint>& point, const Tuple<T, 3, tagVector>& normal) {
            auto dst = -normal.Dot(point.GetRadiusVector());
            m_plane.Set(normal[0], normal[1], normal[2], dst);
        }

        TPlane(const Tuple<T, 3, tagVector>& normal, T distances) : m_plane(normal[0], normal[1], normal[2], distances)
        {}

        TPlane(const Tuple<T, 3, tagPoint>& a, const Tuple<T, 3, tagPoint>& b, const Tuple<T, 3, tagPoint>& c) {
            Set(a, b, c);
        }

        TPlane(T a, T b, T c, T d) {
            Set(a, b, c, d);
        }

        TPlane(const Tuple<T, 4, tagVector>& plane)
            : m_plane(plane)
        {}

        TPlane<T>& operator = (const TPlane& plane)
        {
            if (this != &plane)
            {
                m_plane = plane.m_plane;
            }
            return *this;
        }

        TPlane<T>& Set(const Tuple<T, 3, tagPoint>& a, const Tuple<T, 3, tagPoint>& b, const Tuple<T, 3, tagPoint>& c)
        {
            Tuple<T, 3, tagVector> normal = (b-a).Cross(c-a).Normalized();
            auto distance = -normal.Dot(a);
            m_plane.Set(normal[0], normal[1], normal[2], distance);
            return *this;
        }

        const TPlane<T> Transform(const Matrix<T, 4, 4>& matrix) const
        {
            Matrix<T, 4, 4 > m = matrix.Inversed().Transposed();
            Tuple<T, 4, tagVector> res = m * m_plane;
            return TPlane<T>(res);
        }

        TPlane<T>& Set(T a, T b, T c, T d)
        {
            m_plane.Set(a, b, c, d);
            return *this;
        }

        TPlane<T>& Set(const Line<T, 3>& line, const Tuple<T, 3, tagPoint>& point)
        {
            const Tuple<T, 3, tagVector> v = (point - line.GetOrigin()).Normalized();
            const Tuple<T, 3, tagVector> normal = line.GetDirection().Cross(v).Normalized();
            T distance = -normal.Dot(point.GetRadiusVector());
            return Set(normal, distance);
        }

        TPlane<T>& Set(const Tuple<T, 3, tagVector>& normal, T dst) {
            m_plane.Set(normal[0], normal[1], normal[2], dst);
            return *this;
        }

        TPlane<T>& Set(const Tuple<T, 4, tagVector>& value) {
            m_plane = value;
            return *this;
        }

        const Tuple<T, 3, tagVector> GetNormal() const {
            return m_plane.XYZ();
        }

        T GetDistance() const {
            return m_plane.W();
        }

        const Tuple<T, 4, tagVector>& AsVector() const {
            return m_plane;
        }

        const Core::String ToString() const {
            return m_plane.ToString();
        }

        TPlane& Normalize() {
            T f = T{1} / (Tuple<T, 3, tagVector>{m_plane.XYZ()}).Length();
            m_plane *= f;
            return *this;
        }

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint>& p) {
			auto s = *this * p;
			if (s < -Eps)
				return Relation::BACK;
			if (s > Eps)
				return Relation::FRONT;
			return Relation::ON;
		}

		Relation ClassifyLine(const Line<T, 3>& line) {
			auto n = this->GetNormal();
			T org_dst = this->GetDistance();
			auto dir = line.GetDirection();
			T v = n.Dot(dir);

			if (Abs(v) < Eps)
			{
				T dst = n.Dot(line.GetOrigin()) + org_dst;
				if (Abs(dst) < Eps)
					return Relation::ON;
				if (dst < 0)
					return Relation::BACK;
				if (dst > 0)
					return Relation::FRONT;
			}
			return Relation::INTERSECT;
		}

		Relation CrossLine(const Line<T, 3>& line, T& t)
		{
			const auto org = line.GetOrigin();
			const auto dst = line.GetDestination();
			const auto dir = dst - org;
			T v = *this * vec4(dir, 0);
			T distance = p * org;

			if (Abs(v) < Eps)
			{
				if (Math::Abs(distance) < Eps)
					return Relation::ON;
				if (distance < 0)
					return Relation::BACK;
				if (distance > 0)
					return Relation::FRONT;
			}
			t = -distance / v;
			return Relation::INTERSECT;
		}

		Relation CrossLine(const Line<T, 3>& line, Tuple<T, 3, tagPoint>& point) const
		{
			T t = 0;
			Relation res = this->CrossLine(line, p, t);
			point = line.PointAt(t);
			return res;
		}

		Relation CrossPlane(const TPlane<T>& plane, Line<T, 3>& line) const
		{
			const auto n1 = this->GetNormal();
			const auto n2 = plane.GetNormal();

			if (Abs(n1.Dot(n2)) > T{ 1.0 } - Eps)
				return Relation::NOT_INTERSECT;

			auto dir = n1.Cross(n2).Normalized();

			TPlane<T> c(dir, 0);

			const auto n3 = c.GetNormal();

			Matrix<T, 3, 3> m;
			m.SetRow(0, n1);
			m.SetRow(1, n2);
			m.SetRow(2, n3);

			T det = m.Determinant();

			if (Abs(det) < Eps)
				return Relation::NOT_INTERSECT;

			Tuple<T, 3, tagPoint> p{ -this->GetDistance(), -plane.GetDistance(), -c.GetDistance() };
			Tuple<T, 3, tagPoint> org = m.Inversed() * p;

			line.SetOriginDirection(org, dir);

			return Relation::INTERSECT;
		}

		Relation ClipExteriorLine(const Line<T, 3>& line, Line<T, 3>& ray)
		{
			auto org = line.GetOrigin();
			auto dst = line.GetDestination();
			auto dir = line.GetDirection();
			auto normal = plane.GetNormal();
			auto s = dir.Dot(normal);
			auto org_relative = ClassifyPoint(org, plane);
			auto dst_relative = ClassifyPoint(dst, plane);

			//	find intersection point
			T t;
			if (plane.CrossLine(line, t) != Relation::INTERSECT)
				return Relation::NOT_INTERSECT;

			if (t < 0 || t > 1)
				return Relation::NOT_INTERSECT;

			//	line segment on negative halfplane (1)
			if (s <= 0 && org_relative == Relation::BACK)
				return Relation::NOT_INTERSECT;

			//	line segment on negative halfplane (2)
			if (s >= 0 && dst_relative == Relation::BACK)
				return Relation::NOT_INTERSECT;

			//	clip line segment to put dst on the plane (3)
			if (s <= 0 && dst_relative == Relation::FRONT)
			{
				auto new_dst = line.PointAt(t);
				ray.SetOriginDestination(org, new_dst);
				return Relation::INTERSECT;
			}

			// clip line segment to put origin on the plane (4)
			if (s >= 0 && org_relative == Relation::FRONT)
			{
				auto new_org = line.PointAt(t);
				ray.SetOriginDestination(new_org, dst);
				return Relation::INTERSECT;
			}

			//	(5)
			if (org_relative == Relation::FRONT && dst_relative == Relation::BACK)
			{
				auto new_dst = line.PointAt(t);
				ray.SetOriginDestination(org, new_dst);
				return Relation::INTERSECT;
			}

			//	(6)
			if (org_relative == Relation::BACK && dst_relative == Relation::FRONT)
			{
				auto new_org = line.PointAt(t);
				ray.SetOriginDestination(new_org, dst);
				return Relation::INTERSECT;
			}

			ray = line;

			return Relation::INTERSECT;
		}

		static Relation CrossThreePlanes(const TPlane<T>& a, const TPlane<T>& b, const TPlane<T>& c, Tuple<T, 3, tagPoint>& vec)
		{
			Line<T, 3> line;
			if (a.CrossPlane(a, line) != Relation::INTERSECT)
				return Relation::NOT_INTERSECT;

			return c.CrossLine(line, vec);
		}

		static Relation CrossPlanes(const std::vector<TPlane<T>>& planes, std::vector<Line<T, 3>>& lines)
		{
			std::size_t size = planes.size();
			for (auto i = 0u; i != size; ++i)
			{
				for (auto j = i + 1; j != size; ++j)
				{
					Line<T, 3> line;
					auto res = planes[i].CrossPlane(planes[j], line);
					if (res == Relation::INTERSECT)
						lines.push_back(line);
				}
			}
			if (lines.empty())
				return Relation::NOT_INTERSECT;
			return Relation::INTERSECT;
		}

    private:
        Tuple<T, 4, tagVector> m_plane;
    };

    template<class T>
    const T operator * (const TPlane<T>& plane, const Tuple<T, 3, tagPoint>& v) {
        T res = plane.AsVector().Dot({v[0], v[1], v[2], 1});
        return res;
    }

    template<class T>
    const T operator * (const TPlane<T>& plane, const Tuple<T, 3, tagVector>& v) {
        T res = plane.AsVector().Dot(v);
        return res;
    }

    template<class T>
    const TPlane<T> operator * (const Matrix<T, 4, 4>& m, const TPlane<T>& p) {
        TPlane<T> res(m * p.AsVector());
        return res;
    }

    using Plane = TPlane<float>;
}
PUNK_ENGINE_END

#endif
