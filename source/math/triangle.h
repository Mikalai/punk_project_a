#ifndef _H_TRIANGLE
#define _H_TRIANGLE

#include <config.h>
#include "relations.h"
#include "min_max.h"
#include "tuple.h"
#include "line.h"
#include "aabb.h"
#include "plane.h"
#include "absolute_value.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T, int Dim> class Triangle;

	template<class T, int Dim>
	struct TriangleData {

		TriangleData() {}

		TriangleData(
			const Tuple<T, Dim, tagPoint>& v0, 
			const Tuple<T, Dim, tagPoint>& v1, 
			const Tuple<T, Dim, tagPoint>& v2) {

			this->m_v[0] = v0; this->m_v[1] = v1; this->m_v[2] = v2;
		}

		Tuple<T, Dim, tagPoint> m_v[3];
	};

	template<class T>
	struct TriangleData < T, 3 > {

		TriangleData() {}

		TriangleData(			
			const Tuple<T, 3, tagPoint>& v0, 
			const Tuple<T, 3, tagPoint>& v1, 
			const Tuple<T, 3, tagPoint>& v2) {

			this->m_v[0] = v0; this->m_v[1] = v1; this->m_v[2] = v2;
			this->m_bbox.MinPoint().X() = Min(v0.X(), v1.X(), v2.X());
			this->m_bbox.MinPoint().Y() = Min(v0.Y(), v1.Y(), v2.Y());
			this->m_bbox.MinPoint().Z() = Min(v0.Z(), v1.Z(), v2.Z());
			this->m_bbox.MaxPoint().X() = Max(v0.X(), v1.X(), v2.X());
			this->m_bbox.MaxPoint().Y() = Max(v0.Y(), v1.Y(), v2.Y());
			this->m_bbox.MaxPoint().Z() = Max(v0.Z(), v1.Z(), v2.Z());
			this->m_normal = (v1 - v0).Cross(v2 - v0);
			this->m_normal.Normalize();
			this->m_distance = -this->m_normal.Dot(v0);
		}

		Tuple<T, 3, tagPoint> m_v[3];
		Tuple<T, 3, tagVector> m_normal;
		T m_distance;
		TAxisAlignedBox<T> m_bbox;
	};


	template<class T, int Dim>
	struct TriangleAccessorBase : public TriangleData < T, Dim > {

		using TriangleData<T, Dim>::TriangleData;

		TriangleAccessorBase() {}

		TriangleAccessorBase(const TriangleData<T, Dim>& value)
			: TriangleData<T, Dim>(value) {}

		const Tuple<T, Dim, tagPoint>& operator[] (std::uint32_t i) const
		{
			return this->m_v[i];
		}

		Tuple<T, Dim, tagPoint>& operator[] (std::uint32_t i)
		{
			return this->m_v[i];
		}
	};

	template<class T, int Dim>
	struct TriangleAccessor : public TriangleAccessorBase < T, Dim > {
		using TriangleAccessorBase<T, Dim>::TriangleAccessorBase;

		TriangleAccessor() {}

		TriangleAccessor(const TriangleData<T, Dim>& value)
			: TriangleAccessorBase<T, Dim>(value) {}
	};

	template<class T>
	struct TriangleAccessor<T, 3> : public TriangleAccessorBase < T, 3 >{

		using TriangleAccessorBase<T, 3>::TriangleAccessorBase;

		TriangleAccessor() {}

		TriangleAccessor(const TriangleData<T, 3>& value)
			: TriangleAccessorBase<T, 3>(value) {}

		const TAxisAlignedBox<T>& GetAxisAlignedBox() const
		{
			return this->m_bbox;
		}

		const Tuple<T, 3, tagVector>& GetNormal() const
		{
			return this->m_normal;
		}

		bool GetBarycentric(const Tuple<T, 3, tagPoint>& p, T& w0, T& w1, T& w2) const
		{
            auto r = p - this->m_v[0];
            auto q1 = this->m_v[1] - this->m_v[0];
            auto q2 = this->m_v[2] - this->m_v[0];
			T q1_q2 = q1.Dot(q2);
			T r_q1 = r.Dot(q1);
			T r_q2 = r.Dot(q2);
			T q1_q1 = q1.Dot(q1);
			T q2_q2 = q2.Dot(q2);

			T inv_det = 1.0f / (q1_q1*q2_q2 - q1_q2*q1_q2);
			w1 = inv_det*(q2_q2*r_q1 - q1_q2*r_q2);
			w2 = inv_det*(-q1_q2*r_q1 + q1_q1*r_q2);
			w0 = 1.0f - w1 - w2;
			return true;
		}
	};

	template<class T, int Dim>
	struct TriangleOperationsBase : public TriangleAccessor < T, Dim > {
		using TriangleAccessor<T, Dim>::TriangleAccessor;

		TriangleOperationsBase() {}

		TriangleOperationsBase(const TriangleData<T, Dim>& value)
			: TriangleAccessor< T, Dim >(value) {}
	};

	template<class T, int Dim>
	struct TriangleOperations : public TriangleOperationsBase < T, Dim > {
		using TriangleOperationsBase<T, Dim>::TriangleOperationsBase;

		TriangleOperations() {}

		TriangleOperations(const TriangleData<T, Dim>& value)
			: TriangleOperationsBase < T, Dim >(value) {}

	};

	template<class T>
	struct TriangleOperations<T, 3> : public TriangleOperationsBase < T, 3 > {

		using TriangleOperationsBase<T, 3>::TriangleOperationsBase;

		TriangleOperations() {}

		TriangleOperations(const TriangleData<T, 2>& value)
			: TriangleOperationsBase < T, 2 >(value) {}

		const TriangleData<T, 2> ProjectXY() const {
			return TriangleData < T, 2 > {
					{this->m_v[0].X(), this->m_v[0].Y()},
					{ this->m_v[1].X(), this->m_v[1].Y() },
					{ this->m_v[2].X(), this->m_v[2].Y() }};
		}

		const TriangleData<T, 2> ProjectXZ() const {
            return TriangleData < T, 2> {
					{this->m_v[0].X(), this->m_v[0].Z()},
					{ this->m_v[1].X(), this->m_v[1].Z() },
					{ this->m_v[2].X(), this->m_v[2].Z() }};
		}

		const TriangleData<T, 2> ProjectYZ() const {
			return TriangleData < T, 2 > {
					{this->m_v[0].Y(), this->m_v[0].Z()},
					{ this->m_v[1].Y(), this->m_v[1].Z() },
					{ this->m_v[2].Y(), this->m_v[2].Z() }};
		}

		Relation ClassifyLine(const Line<T, 3>& line)
		{
			const auto org = line.GetOrigin();
			const auto n = this->GetNormal();
			T org_dst = this->GetDistance();
			const auto dir = line.GetDirection();
			T v = n.Dot(dir);

			if (Abs(v) < Eps)
			{
				T dst = n.Dot(org) + org_dst;
				if (Abs(dst) < Eps)
					return Relation::ON;
				if (dst < 0)
					return Relation::BACK;
				if (dst > 0)
					return Relation::FRONT;
			}

			T t = -(n.Dot(org) + org_dst) / v;
			const auto intersect_point = line.PointAt(t);

            Relation res = this->ClassifyPoint(intersect_point);

			if (res != Relation::INSIDE)
				return Relation::INTERSECT;

			return Relation::NOT_INTERSECT;
		}

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint>& p)
		{
			const auto n = this->GetNormal();
			T org_dst = this->GetDistance();

			T dst = p.Dot(n) + org_dst;

			if (Abs(dst) < Eps)	//	point on the same plane as triangle
			{
				T w0, w1, w2;
				this->GetBarycentric(p, w0, w1, w2);

				if (w0 < -Eps || w1 < -Eps || w2 < -Eps)
					return Relation::OUTSIDE;
				if (Abs(1.0f - w0) < Eps)
					return Relation::A;
				if (Abs(1.0f - w1) < Eps)
					return Relation::B;
				if (Abs(1.0f - w2) < Eps)
					return Relation::C;
				if (Abs(w0) < Eps)
					return Relation::BC;
				if (Abs(w1) < Eps)
					return Relation::CA;
				if (Abs(w2) < Eps)
					return Relation::AB;
				if (w0 > 0 && w1 > 0 && w2 > 0)
					return Relation::INSIDE;
				return Relation::OUTSIDE;
			}

			if (dst < 0.0f)
				return Relation::BACK;
			return Relation::FRONT;
		}

		Relation CrossLine(const Line<T, 3>& line, T& t)
		{
			const auto org = line.GetOrigin();
			const auto n = this->GetNormal();
			T org_dst = this->GetDistance();
			const auto dir = line.GetDestination() - line.GetOrigin();
			T v = n.Dot(dir);

			if (Abs(v) < Eps)
			{
				T dst = n.Dot(org) + org_dst;
				if (Abs(dst) < Eps)
					return Relation::ON;
				if (dst < 0)
					return Relation::BACK;
				if (dst > 0)
					return Relation::FRONT;
			}

			t = -(n.Dot(org) + org_dst) / v;
			const auto intersect_point = line.PointAt(t);

			Relation res = this->ClassifyPoint(intersect_point);

			if (res == Relation::INSIDE)
				return Relation::INTERSECT;
			return Relation::NOT_INTERSECT;
		}

		Relation CrossLine(const Line<T, 3>& line, Tuple<T, 3, tagPoint>& vec)
		{
			T t = 0;
			Relation res = this->CrossLine(line, t);
			vec = line.PointAt(t);
			return res;
		}

		Relation CrossPlaneTriangle(const Plane& plane, const Triangle<T, 3>& tr, Line<T, 3>& line)
		{
			Relation res;
			Line<T, 3> ab(tr[0], tr[1]);
			Line<T, 3> bc(tr[1], tr[2]);
			Line<T, 3> ca(tr[2], tr[0]);

			Tuple<T, 3, tagPoint> p[2];
			auto* cur = p;
			T t;

			res = plane.CrossLine(ab, t);
			if (res == Relation::INTERSECT && t >= 0.0f && t <= 1.0f)
				(*cur = ab.PointAt(t), ++cur);

			res = plane.CrossLine(bc, t);
			if (res == Relation::INTERSECT && t >= 0.0f && t <= 1.0f)
				(*cur = bc.PointAt(t), ++cur);

			res = plane.CrossLine(ca, t);
			if (res == Relation::INTERSECT && t >= 0.0f && t <= 1.0f)
				(*cur = ca.PointAt(t), ++cur);

			if (cur == p + 1)	//	we got two points
			{
				line.SetOriginDestination(p[0], p[1]);
				return Relation::INTERSECT;
			}
			return Relation::NOT_INTERSECT;
		}

		Relation CrossTriangle(const Triangle<T, 3>& b, Line<T, 3>& /*line*/)
		{
            Line<T, 3> ab(this->m_v[0], this->m_v[1]);
            Line<T, 3> bc(this->m_v[1], this->m_v[2]);
            Line<T, 3> ca(this->m_v[2], this->m_v[0]);

			Line<T, 3> de(b[0], b[1]);
			Line<T, 3> ef(b[1], b[2]);
			Line<T, 3> fd(b[2], b[0]);

			//
			//  cross firs tr with second
			//
			T s = 0;
			if (b.CrossLine(ab, s) == Relation::INTERSECT)
				if (s >= 0 && s <= 1)
					return Relation::INTERSECT;
			if (b.CrossLine(bc, s) == Relation::INTERSECT)
				if (s >= 0 && s <= 1)
					return Relation::INTERSECT;
			if (b.CrossLine(ca, s) == Relation::INTERSECT)
				if (s >= 0 && s <= 1)
					return Relation::INTERSECT;

			//
			//  cross second tr with firs
			//
			if (b.CrossLine(de, s) == Relation::INTERSECT)
				if (s >= 0 && s <= 1)
					return Relation::INTERSECT;
			if (b.CrossLine(ef, s) == Relation::INTERSECT)
				if (s >= 0 && s <= 1)
					return Relation::INTERSECT;
			if (b.CrossLine(fd, s) == Relation::INTERSECT)
				if (s >= 0 && s <= 1)
					return Relation::INTERSECT;
			return Relation::NOT_INTERSECT;
		}

		Relation CrossAxisAlignedBox(const TAxisAlignedBox<T>& aabb)
		{
			auto pp1 = this->m_v[0];
			auto pp2 = this->m_v[1];
			auto pp3 = this->m_v[2];

			if (pp1[0] > aabb.MaxPoint()[0] && pp2[0] > aabb.MaxPoint()[0] && pp3[0] > aabb.MaxPoint()[0])
				return Relation::NOT_INTERSECT;
			if (pp1[0] < aabb.MinPoint()[0] && pp2[0] < aabb.MinPoint()[0] && pp3[0] < aabb.MinPoint()[0])
				return Relation::NOT_INTERSECT;
			if (pp1[1] > aabb.MaxPoint()[1] && pp2[1] > aabb.MaxPoint()[1] && pp3[1] > aabb.MaxPoint()[1])
				return Relation::NOT_INTERSECT;
			if (pp1[1] < aabb.MinPoint()[1] && pp2[1] < aabb.MinPoint()[1] && pp3[1] < aabb.MinPoint()[1])
				return Relation::NOT_INTERSECT;
			if (pp1[2] > aabb.MaxPoint()[2] && pp2[2] > aabb.MaxPoint()[2] && pp3[2] > aabb.MaxPoint()[2])
				return Relation::NOT_INTERSECT;
			if (pp1[2] < aabb.MinPoint()[2] && pp2[2] < aabb.MinPoint()[2] && pp3[2] < aabb.MinPoint()[2])
				return Relation::NOT_INTERSECT;
			//
			//  the simpliest test
			//
			if (ClassifyPoint(pp1, aabb) == Relation::INSIDE
				|| ClassifyPoint(pp2, aabb) == Relation::INSIDE
				|| ClassifyPoint(pp3, aabb) == Relation::INSIDE)
				return Relation::INTERSECT;

			if (ClipSegment3D(pp1, pp2, aabb.MinPoint(), aabb.MaxPoint()))
				return Relation::INTERSECT;
			if (ClipSegment3D(pp2, pp3, aabb.MinPoint(), aabb.MaxPoint()))
				return Relation::INTERSECT;
			if (ClipSegment3D(pp3, pp1, aabb.MinPoint(), aabb.MaxPoint()))
				return Relation::INTERSECT;

			return Relation::NOT_INTERSECT;
		}

        Relation SplitTriangle(const Plane& splitter, Triangle<T, 3> front[2], Triangle<T, 3> back[2])
		{
            Plane plane(this->m_v[0], this->m_v[1], this->m_v[2]);
            T ss0 = splitter.GetNormal().Dot(this->m_v[0]) + splitter.GetDistance();
            T ss1 = splitter.GetNormal().Dot(this->m_v[1]) + splitter.GetDistance();
            T ss2 = splitter.GetNormal().Dot(this->m_v[2]) + splitter.GetDistance();
			int s0, s1, s2;

			if (Abs(ss0) < Eps)
				s0 = 0;
			if (Abs(ss1) < Eps)
				s1 = 0;
			if (Abs(ss2) < Eps)
				s2 = 0;

			if (s0 == 0 && s1 == 0 && s2 == 0)
				return Relation::NO_SPLIT_ON;

			if (s0 <= 0 && s1 <= 0 && s2 <= 0)
				return Relation::NO_SPLIT_BACK;

			if (s0 >= 0 && s1 >= 0 && s2 >= 0)
				return Relation::NO_SPLIT_FRONT;

			Triangle<T, 3>* cur_front = front;
			Triangle<T, 3>* cur_back = back;

			if (s0 == 0)	//	split on front and back
			{
                Line<T, 3> l{ this->m_v[1], this->m_v[2] };
				Tuple<T, 3, tagPoint> p;
				Relation r = splitter.CrossLine(l, p);

				if (r != Relation::NOT_INTERSECT)
					return r;

				if (s1 <= 0 && s2 >= 0)
				{
                    (*cur_back) = Triangle<T, 3>(this->m_v[0], this->m_v[1], p);
                    (*cur_front) = Triangle<T, 3>(p, this->m_v[2], this->m_v[0]);
					return Relation::SPLIT_1_FRONT_1_BACK;
				}
				else
				{
                    (*cur_back) = Triangle<T, 3>(p, this->m_v[2], this->m_v[0]);
                    (*cur_front) = Triangle<T, 3>(this->m_v[0], this->m_v[1], p);
					return Relation::SPLIT_1_FRONT_1_BACK;
				}
			}

			if (s1 == 0)	//	split on front and back
			{
                Line<T, 3> l(this->m_v[2], this->m_v[0]);
				Tuple<T, 3, tagPoint> p;
				Relation r = splitter.CrossLine(l, p);

				if (r != Relation::NOT_INTERSECT)
					throw Error::UnexpectedResult(0);

				if (s0 <= 0 && s2 >= 0)
				{
                    (*cur_back) = Triangle<T, 3>(this->m_v[1], p, this->m_v[0]);
                    (*cur_front) = Triangle<T, 3>(this->m_v[1], this->m_v[2], p);
					return Relation::SPLIT_1_FRONT_1_BACK;
				}
				else
				{
                    (*cur_back) = Triangle<T, 3>(this->m_v[1], this->m_v[2], p);
                    (*cur_front) = Triangle<T, 3>(this->m_v[1], p, this->m_v[0]);
					return Relation::SPLIT_1_FRONT_1_BACK;
				}
			}

			if (s2 == 0)	//	split on front and back
			{
                Line<T, 3> l(this->m_v[0], this->m_v[1]);
				Tuple<T, 3, tagPoint> p;
				Relation r = splitter.CrossLine(l, p);

				if (r != Relation::NOT_INTERSECT)
					throw Error::UnexpectedResult(0);

				if (s0 <= 0 && s1 >= 0)
				{
                    (*cur_back) = Triangle<T, 3>(this->m_v[2], this->m_v[0], p);
                    (*cur_front) = Triangle<T, 3>(this->m_v[2], p, this->m_v[1]);
					return Relation::SPLIT_1_FRONT_1_BACK;
				}
				else
				{
                    (*cur_front) = Triangle<T, 3>(this->m_v[2], this->m_v[0], p);
                    (*cur_back) = Triangle<T, 3>(this->m_v[2], p, this->m_v[1]);
					return Relation::SPLIT_1_FRONT_1_BACK;
				}
			}

            const Tuple<T, 3, tagPoint>* a = &this->m_v[0];
            const Tuple<T, 3, tagPoint>* b = &this->m_v[1];
            const Tuple<T, 3, tagPoint>* c = &this->m_v[2];

			Relation result = Relation::SPLIT_1_FRONT_2_BACK;

			//	common case
			if ((s1 < 0 && s2 < 0) || (s1 > 0 && s2 > 0))
			{
                a = &this->m_v[0];
                b = &this->m_v[1];
                c = &this->m_v[2];
			}

			if ((s2 < 0 && s0 < 0) || (s2 > 0 && s0 > 0))
			{
                a = &this->m_v[1];
                b = &this->m_v[2];
                c = &this->m_v[0];
			}

			if ((s0 < 0 && s1 < 0) || (s0 > 0 && s1 > 0))
			{
                a = &this->m_v[2];
                b = &this->m_v[0];
                c = &this->m_v[1];
			}

			if (s1 < 0)
			{
				std::swap(cur_front, cur_back);
				result = Relation::SPLIT_2_FRONT_1_BACK;
			}


			const Line<T, 3> ab(*a, *b);
			const Line<T, 3> ac(*a, *c);

			Tuple<T, 3, tagPoint> bb, cc;
			Relation r = splitter.CrossLine(ab, bb);
			if (r == Relation::NOT_INTERSECT)
				throw Error::UnexpectedResult(0);

			r = splitter.CrossLine(ac, cc);
			if (r == Relation::NOT_INTERSECT)
				throw Error::UnexpectedResult(0);

			*cur_front = Triangle<T, 3>(*a, bb, cc);
			*cur_back++ = Triangle<T, 3>(bb, *b, *c);
			*cur_back = Triangle<T, 3>(bb, *c, cc);

			return result;
		}
	};


	template<class T>
	struct TriangleOperations<T, 2> : public TriangleOperationsBase < T, 2 > {

		using TriangleOperationsBase<T, 2>::TriangleOperationsBase;

		TriangleOperations() {}

		TriangleOperations(const TriangleData<T, 2>& value)
			: TriangleOperationsBase < T, 2 >(value) {}

		bool IsPointIn(const Tuple<T, 2, tagPoint>& p) const {
			auto a = this->m_v[0];
			auto b = this->m_v[1];
			auto c = this->m_v[2];
			T s1 = (a.X() - p.X()) * (b.Y() - p.Y()) - (a.Y() - p.Y()) * (b.X() - p.X());
			T s2 = (b.X() - p.X()) * (c.Y() - p.Y()) - (b.Y() - p.Y()) * (c.X() - p.X());
			T s3 = (c.X() - p.X()) * (a.Y() - p.Y()) - (c.Y() - p.Y()) * (a.X() - p.X());
			s1 = (Abs(s1) <= 1e-4) ? 0 : s1;
			s2 = (Abs(s2) <= 1e-4) ? 0 : s2;
			s3 = (Abs(s3) <= 1e-4) ? 0 : s3;
			if (s1 >= 0 && s2 >= 0 && s3 >= 0)
				return true;
			if (s1 <= 0 && s2 <= 0 && s3 <= 0)
				return true;
			return false;
		}
	};

	template<class T, int Dim>
	class Triangle : public TriangleOperations < T, Dim > {
		using TriangleOperations<T, Dim>::TriangleOperations;

		Triangle() {}

		Triangle(const TriangleData<T, Dim>& value)
			: TriangleOperations < T, Dim >(value) {}
	};
}
PUNK_ENGINE_END

#endif
