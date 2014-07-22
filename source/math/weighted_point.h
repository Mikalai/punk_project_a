#ifndef WEIGHTED_POINT_H
#define WEIGHTED_POINT_H

#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T, int D, typename tag>
	class TWeightedPoint {
	public:

		TWeightedPoint()
			: m_weight(1.0)
		{}

		TWeightedPoint(const Tuple<T, D, tag> &value, float weight)
			: m_weight(weight)
			, m_point(value)
		{}

		TWeightedPoint& operator += (const TWeightedPoint& value)
		{
			m_point += value.m_point;
			m_weight += value.m_weight;
			return *this;
		}

		TWeightedPoint& operator -= (const TWeightedPoint& value)
		{
			m_point -= value.m_point;
			m_weight -= value.m_weight;
			return *this;
		}

		TWeightedPoint& operator *= (float value)
		{
			m_point *= value;
			m_weight *= value;
			return *this;
		}

		TWeightedPoint& operator /= (float value)
		{
			m_point /= value;
			m_weight /= value;
			return *this;
		}		

		float Length() const
		{
			return m_point.Length();
		}

		void SetWeight(float value)
		{
			m_weight = value;
		}

		float GetWeight() const
		{
			return m_weight;
		}

		void SetPoint(const Tuple<T, D, tag>& value)
		{
			m_point = value;
		}

		const Tuple<T, D, tag>& GetPoint() const {
			return m_point;
		}


	private:
		T m_weight;
		Tuple<T, D, tag> m_point;
	};

	template<class T, int D, typename tag>
	const TWeightedPoint<T, D, tag> operator + (const TWeightedPoint<T, D, tag>& l, const TWeightedPoint<T, D, tag>& r)
	{
		TWeightedPoint<T, D, tag> res(l);
		res += r;
		return res;
	}

	template<class T, int D, typename tag>
	const TWeightedPoint<T, D, tag> operator - (const TWeightedPoint<T, D, tag>& l, const TWeightedPoint<T, D, tag>& r)
	{
		TWeightedPoint<T, D, tag> res(l);
		res -= r;
		return res;
	}

	template<class T, int D, typename tag>
	const TWeightedPoint<T, D, tag> operator * (const TWeightedPoint<T, D, tag>& l, float r)
	{
		TWeightedPoint<T, D, tag> res(l);
		res *= r;
		return res;
	}

	template<class T, int D, typename tag>
	const TWeightedPoint<T, D, tag> operator * (float l, const TWeightedPoint<T, D, tag>& r)
	{
		TWeightedPoint<T, D, tag> res(r);
		res *= l;
		return res;
	}

	template<class T, int D, typename tag>
	const TWeightedPoint<T, D, tag> operator / (const TWeightedPoint<T, D, tag>& l, float r)
	{
		TWeightedPoint<T, D, tag> res(l);
		res /= r;
		return res;
	}

	template<class T, int D, typename tag>
	const TWeightedPoint<T, D, tag> operator / (float l, const TWeightedPoint<T, D, tag>& r)
	{
		TWeightedPoint<T, D, tag> res(r);
		res /= l;
		return res;
	}

	using WeightedPoint = TWeightedPoint < float, 3, tagPoint > ;
}
PUNK_ENGINE_END

#endif // WEIGHTED_POINT_H
