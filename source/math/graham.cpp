#include <math.h>
#include <algorithm>
#include "relations.h"
#include "graham.h"
#include "tuple.h"
#include "matrix.h"

namespace Punk {
	namespace Engine {
		namespace Math {

			bool operator < (const point2d& l, const point2d& r)
			{
				if (l.Y() < r.Y())
					return true;
				if (l.Y() == r.Y())
				if (l.X() < r.X())
					return true;
				else
					return false;
				return false;
			}

			struct Sort
			{
				Sort(point2d p0)
				: m_p0(p0)
				{}

				float theta(const point2d& p)
				{
					float dx = p.X() - m_p0.X();
					float dy = p.Y() - m_p0.Y();
					return atan2f(dy, dx);
				}

				float distance(const point2d& p)
				{
					float dx = p.X() - m_p0.X();
					float dy = p.Y() - m_p0.Y();
					return dx * sqrtf(1.0f + powf(dy / dx, 2.0f));
				}

				bool operator () (const point2d& l, const point2d& r)
				{
					float theta1 = theta(l);
					float theta2 = theta(r);
					if (theta1 < theta2)
						return true;
					if (theta1 == theta2)
					{
						float dst1 = distance(l);
						float dst2 = distance(r);
						return dst1 < dst2;
					}
					return false;
				}

				point2d m_p0;
			};

			void SortPointsForGrahamAlgorithm(std::vector<point2d> &points)
			{
				//	find min p
				int min = 0;
				for (int i = 1, max_i = (int)points.size(); i != max_i; ++i)
				{
					if (points[i].Y() < points[min].Y())
						min = i;
					else
					if (points[i].Y() == points[min].Y())
					if (points[i].X() < points[min].X())
						min = i;
				}

				std::swap(points[min], points[0]);

				//	sort
				std::sort(points.begin() + 1, points.end(), Sort(points[0]));
			}

			void CreateConvexHullFromSortedPoint(const std::vector<point2d> &points, std::vector<point2d> &stack)
			{
				stack.clear();
				stack.push_back(points[0]);
				stack.push_back(points[1]);

				for (int i = 2, max_i = (int)points.size(); i < max_i; ++i)
				{
					const auto* a = &stack[stack.size() - 2];
					const auto* b = &stack[stack.size() - 1];
					const auto* c = &points[i];
					while (!vec2::IsLeftRotation(*a, *b, *c))
					{
						stack.pop_back();
						a = &stack[stack.size() - 2];
						b = &stack[stack.size() - 1];
						c = &points[i];
					}
					stack.push_back(points[i]);
				}
			}

			void CreateConvexHull(std::vector<point2d> points, std::vector<point2d> &result)
			{
				SortPointsForGrahamAlgorithm(points);
				CreateConvexHullFromSortedPoint(points, result);
			}
		}
	}
}