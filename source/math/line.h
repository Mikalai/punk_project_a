#ifndef ANY_LINE_H
#define ANY_LINE_H

#include "config.h"
#include "tuple.h"
#include "matrix.h"
#include "constants.h"
#include "relations.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T, int Dim> class Line;

	template<class T, int Dim>
	struct LineData {

		LineData() {
			m_direction[0] = T{ 1 };
			m_destination[0] = T{ 1 };
		}

		LineData(const Tuple<T, Dim, tagPoint>& org, const Tuple<T, Dim, tagPoint>& dst)
			: m_origin(org)
			, m_destination(dst)
			, m_direction((dst - org).Normalized())
		{}

		LineData(const Tuple<T, Dim, tagPoint>& org, const Tuple<T, Dim, tagVector>& dir)
			: m_origin(org)
			, m_destination(org + dir)
			, m_direction(dir.Normalized())
		{}

	protected:
		Math::Tuple<T, Dim, tagPoint> m_origin;
		Math::Tuple<T, Dim, tagPoint> m_destination;
		Math::Tuple<T, Dim, tagVector> m_direction;
	};

	template<class T, int Dim>
	struct LineAccessorBase : public LineData < T, Dim > {
		using LineData<T, Dim>::LineData;

		LineAccessorBase() {}

		LineAccessorBase(const LineData<T, Dim>& value)
			: LineData < T, Dim >(value) {}

		void SetOrigin(const Tuple<T, Dim, tagPoint>& origin)
		{
			this->m_origin = origin;
			this->m_direction = (this->m_destination - this->m_origin).Normalized();
		}

		void SetDestination(const Tuple<T, Dim, tagPoint>& destination)
		{
			this->m_destination = destination;
			this->m_direction = (this->m_destination - this->m_origin).Normalized();
		}

		void SetOriginDirection(const Tuple<T, Dim, tagPoint>& org, const Tuple<T, Dim, tagVector>& dir)
		{
			this->m_origin = org;
			this->m_direction = dir;
			this->m_destination = this->m_origin + this->m_direction;
		}

		void SetOriginDestination(const Tuple<T, Dim, tagPoint>& org, const Tuple<T, Dim, tagPoint>& dst)
		{
			this->m_origin = org;
			this->m_destination = dst;
			this->m_direction = (this->m_destination - this->m_origin).Normalized();
		}

		const Tuple<T, Dim, tagPoint>& GetOrigin() const {
			return this->m_origin;
		}

		Tuple<T, Dim, tagPoint>& GetOrigin() {
			return this->m_origin;
		}

		const Tuple<T, Dim, tagPoint>& GetDestination() const {
			return this->m_destination;
		}

		Tuple<T, Dim, tagPoint>& GetDestination() {
			return this->m_destination;
		}

		const Tuple<T, Dim, tagVector> GetDirection() const {
			return this->m_direction;
		}
	};


	template<class T, int Dim>
	struct LineAccessor : public LineAccessorBase < T, Dim > {
		using LineAccessorBase<T, Dim>::LineAccessorBase;

		LineAccessor() {}

		LineAccessor(const LineData<T, Dim>& value)
			: LineAccessorBase < T, Dim >(value) {}

	};

	template<class T, int Dim>
	struct LineOperationsBase : public LineAccessor < T, Dim > {
		using LineAccessor<T, Dim>::LineAccessor;

		LineOperationsBase() {}

		LineOperationsBase(const LineData<T, Dim>& value)
			: LineAccessor < T, Dim >(value) {}

		const Tuple<T, Dim, tagPoint> PointAt(float t) const
		{
			return this->m_origin + t * (this->m_destination - this->m_origin);
		}

		T GetSegmentLength() const
		{
			auto res = (this->m_destination - this->m_origin).Length();
			return res;
		}		

		const Core::String ToString() const
		{
			Core::String result = L"{Org: "
				+ this->m_origin.ToString() + L"; Dst: "
				+ this->m_destination.ToString() + L" Dir: "
				+ this->m_direction.ToString();
			return result;
		}
	};

	template<class T, int Dim>
	struct LineOperations : public LineOperationsBase < T, Dim > {
		using LineOperationsBase<T, Dim>::LineOperationsBase;

		LineOperations() {}

		LineOperations(const LineData<T, Dim>& value)
			: LineOperationsBase < T, Dim >(value) {}
	};

	template<class T>
	struct LineOperations<T, 3> : public LineOperationsBase < T, 3 > {

		using LineOperationsBase<T, 3>::LineOperationsBase;

		LineOperations() {}

		LineOperations(const LineData<T, 3>& value)
			: LineOperationsBase < T, 3 >(value) {}

		Relation ClassifyPoint(const Tuple<T, 3, tagPoint>& point) const 
		{
			const auto org = this->GetOrigin();
			const auto dst = this->GetDestination();
			const auto dir = dst - org;			
			const auto p = point;
			const auto p_org = p - org;
			const auto p_dir = p - dst;

			if (p_org.SquareLength() < Eps)
				return Relation::START;

			if (p_dir.SquareLength() < Eps)
				return Relation::END;

			if (p_org.Cross(p_dir).SquareLength() < Eps) {
				if (p_dir.Dot(p_org) < 0)
					return Relation::INSIDE;
				if (p_org.Dot(dir) < 0)
					return Relation::FRONT;
				return Relation::BACK;
			}

			return Relation::OUTSIDE;
		}

		Relation CrossLine(const LineOperations<T, 3>& line, T& t1, T& t2, T& dst) const
		{
			auto s1 = this->GetOrigin();
			auto v1 = this->GetDestination() - this->GetOrigin();
			auto s2 = line.GetOrigin();
			auto v2 = line.GetDestination() - line.GetOrigin();

			T k = powf(v1.Dot(v2), T{ 2 }) - v1.SquareLength()*v2.SquareLength();
			if (fabs(k) < 1e-6)
				return Relation::PARALLEL;
			k = T{ 1 } / k;

			T minus_v2_v2 = -v2.Dot(v2);
			T v1_v2 = v1.Dot(v2);
			T minus_v1_v2 = -v1.Dot(v2);
			T v1_v1 = v1.Dot(v1);

			Matrix<T, 2, 2> m;
			m[0] = minus_v2_v2;
			m[1] = minus_v1_v2;
			m[2] = v1_v2;
			m[3] = v1_v1;

			m = { -v2.SquareLength(), v1.Dot(v2), -v1.Dot(v2), v1.SquareLength() };
			m *= k;

			Tuple<T, 2, tagVector> v{ (s2 - s1).Dot(v1), (s2 - s1).Dot(v2) };
			auto res = m * v;
			t1 = res[0];
			t2 = res[1];

			auto p1 = this->PointAt(t1);
			auto p2 = line.PointAt(t2);

			dst = (p1 - p2).Length();

			if (dst < 1e-6)
				return Relation::INTERSECT;

			return Relation::NOT_INTERSECT;
		}

		Relation CrossLine(const LineOperations<T, 3>& line, Tuple<T, 3, tagPoint>& p) const
		{
			T t1;
			T t2;
			T dst;
			auto res = this->CrossLine(line, t1, t2, dst);
			if (res == Relation::INTERSECT)
			{
				auto p1 = this->PointAt(t1);
				auto p2 = line.PointAt(t2);
				p = T{ 0.5 } *(p1 + p2);
			}
			return res;
		}

		Relation GetDistance(const LineOperations<T, 3>& line, T& dst, T& t1, T& t2) const
		{
			const auto s1 = this->GetOrigin();
			const auto s2 = line->GetOrigin();
			const auto v1 = this->GetDestination() - this->GetOrigin();
			const auto v2 = line->GetDestination() - line->GetOrigin();

			T v1_dot_v2 = v1.Dot(v2);
			T v1_dot_v1 = v1.SquareLength();
			T v2_dot_v2 = v2.SquareLength();
			T ds_dot_v1 = (s2 - s1).Dot(v1);
			T ds_dot_v2 = (s2 - s1).Dot(v2);

			t1 = (-v2_dot_v2 * ds_dot_v1 + v1_dot_v2 * ds_dot_v2) / (v1_dot_v2 * v1_dot_v2 - v1_dot_v1 * v2_dot_v2);
			t2 = (v1_dot_v1 * ds_dot_v2 - v1_dot_v2 * ds_dot_v1) / (v1_dot_v2 * v1_dot_v2 - v1_dot_v1 * v2_dot_v2);

			const auto p1 = this->PointAt(t1);
			const auto p2 = line->PointAt(t2);

			dst = (p1 - p2).Length();

			if (dst < Eps)
				return Relation::INTERSECT;

			return Relation::NOT_INTERSECT;
		}

		Relation GetDistance(const Tuple<T, 3, tagPoint>& point, T& dst) const
		{
			const Tuple<T, 3, tagPoint> q = point;
			const Tuple<T, 3, tagPoint> s = this->GetOrigin();
			const Tuple<T, 3, tagPoint> v = this->GetDestination() - this->GetOrigin();

			auto qs = q - s;
			auto qs_dot_v = qs.Dot(v);
			dst = sqrt(qs.Dot(qs) - qs_dot_v * qs_dot_v / v.SquareLength());

			if (dst < 1e-6)
				return Relation::INSIDE;
			return Relation::OUTSIDE;
		}

		static Relation CrossLines(const std::vector<Line<T, 3>>& lines, std::vector<Tuple<T, 3, tagPoint>>& points) 
		{
			points.clear();
			std::size_t count = lines.size();
			for (std::size_t i = 0; i != count - 1; ++i)
			{
				for (std::size_t j = i + 1; j != count; ++j)
				{
					Tuple<T, 3, tagPoint> point;
					if (Relation::INTERSECT == lines[i].CrossLine(lines[j], point))
					{
						points.push_back(point);
					}
				}
			}
			if (points.empty())
				return Relation::NOT_INTERSECT;
			return Relation::INTERSECT;
		}
	};

	template<class T>
	struct LineOperations<T, 2> : public LineOperationsBase < T, 2 > {
		using LineOperationsBase<T, 2>::LineOperationsBase;

		void Flip() {
			Rotate();
			Rotate();
		}

		void Rotate() {
			auto m = 0.5f * (this->m_origin + this->m_destination);
			auto v = this->m_destination - this->m_origin;
			auto n = Tuple < T, 2, tagVector > {v.Y(), -v.X()};
			this->m_origin = m - T{ 0.5 } *n;
			this->m_destination = m + T{ 0.5 } *n;
		}

		T GetDistance(const Tuple<T, 2, tagPoint>& p) const {
			auto ab = *this;
			ab.Flip().Rotate();

			auto n = ab.Destination() - ab.Origin();

			n.Normalize();

			auto f = LineOperations<T, 2>(p, p + n);
			T t = 0;
			Cross(f, t);
			return t;
		}

		Relation ClassifyPoint(const Tuple<T, 2, tagPoint>& point) const {

			const auto org = this->GetOrigin();
			const auto dst = this->GetDestination();
			const auto dir = dst - org;
			const auto p = point;
			const auto p_org = p - org;
			const auto p_dir = p - dst;

			if (p_org.SquareLength() < Eps)
				return Relation::START;

			if (p_dir.SquareLength() < Eps)
				return Relation::END;

			if (p_org.X() * p_dir.Y() - p_dir.X() * p_org.Y() < Eps) {
				if (p_dir.Dot(p_org) < 0)
					return Relation::INSIDE;
				if (p_org.Dot(dir) < 0)
					return Relation::FRONT;
				return Relation::BACK;
			}

			return Relation::OUTSIDE;

		}

		Relation CrossLine(const LineOperations<T, 2>& r, T &t) const {
			auto l = *this;
			auto a = l.GetOrigin();
			auto b = l.GetDestination();
			auto c = r.GetOrigin();
			auto d = r.GetDestination();
			auto n = Tuple<T, 2, tagVector>((d - c).Y(), (c - d).X());
			T denom = n.Dot(b - a);
			if (denom == T{ 0 })
			{
				Relation aclass = r.ClassifyPoint(l.GetOrigin());
				if (aclass != Relation::OUTSIDE)
					return Relation::ON;					
				else
					return Relation::PARALLEL;					
			}

			T num = n.Dot(a - c);
			t = -num / denom;

			return Relation::INTERSECT;
		}
	};

	template<class T, int Dim>
	class Line : public LineOperations < T, Dim > {
	public:
		using LineOperations<T, Dim>::LineOperations;
	};

	template<class T, int Dim>
	const Line<T, Dim> operator * (const Matrix<T, Dim + 1, Dim + 1>& l, const Line<T, Dim>& r) {
		auto org = l * r.GetOrigin();
		auto dst = l * r.GetDestination();
		Line<T, Dim> res{ org, dst };
		return res;
	}
}
PUNK_ENGINE_END

#endif // LINE_H
