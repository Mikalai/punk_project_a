#ifndef _H_CLIP_SEGMENT
#define _H_CLIP_SEGMENT

#include <config.h>
#include "tuple.h"

PUNK_ENGINE_BEGIN
namespace Math {

	template<class T>
	bool ClipSegment(T min, T max, T a, T b, T d, T* t0, T* t1)
	{
		if (fabs(d) < std::numeric_limits<T>().epsilon())
		{
			if (d > 0.0f)
			{
				return !(b < min || a > max);
			}
			else
			{
				return !(a < min || b > max);
			}
		}

		T u0, u1;

		u0 = (min - a) / (d);
		u1 = (max - a) / (d);

		if (u0 > u1)
		{
			T temp = u0;
			u0 = u1;
			u1 = temp;
		}

		if (u1 < *t0 || u0 > *t1)
		{
			return false;
		}

		*t0 = Max(u0, *t0);
		*t1 = Max(u1, *t1);

		if (*t1 < *t0)
		{
			return false;
		}

		return true;
	}

	template<class T>
	bool ClipSegment3D(const Tuple<T, 3, tagPoint>& A, const Tuple<T, 3, tagPoint>& B, const Tuple<T, 3, tagPoint>& min, const Tuple<T, 3, tagPoint>& max)
	{
		T t0 = 0.0f, t1 = 1.0f;
		//		T S[3] = {A[0], A[1], A[2]};
		T D[3] = { B[0] - A[0], B[1] - A[1], B[2] - A[2] };

		if (!ClipSegment(min[0], max[0], A[0], B[0], D[0], &t0, &t1))
		{
			return false;
		}

		if (!ClipSegment(min[1], max[1], A[1], B[1], D[1], &t0, &t1))
		{
			return false;
		}

		if (!ClipSegment(
			min[2], max[2], A[2], B[2], D[2], &t0, &t1))
		{
			return false;
		}

		return true;
	}

	template<class T>
	bool ClipSegment2D(const Tuple<T, 2, tagPoint>& A, const Tuple<T, 2, tagPoint>& B, const Tuple<T, 2, tagPoint>& min, const Tuple<T, 2, tagPoint>& max)
	{
		T t0 = 0.0f, t1 = 1.0f;
		//		T S[2] = {A[0], A[1]};
		T D[2] = { B[0] - A[0], B[1] - A[1] };

		if (!ClipSegment(min[0], max[0], A[0], B[0], D[0], &t0, &t1))
		{
			return false;
		}

		if (!ClipSegment(min[1], max[1], A[1], B[1], D[1], &t0, &t1))
		{
			return false;
		}

		return true;
	}
}
PUNK_ENGINE_END
