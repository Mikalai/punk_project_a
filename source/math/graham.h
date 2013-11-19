#ifndef GRAHAM_H
#define GRAHAM_H

#include <vector>
#include "../config.h"
#include "vec2.h"

namespace Math
{
    PUNK_ENGINE_API void SortPointsForGrahamAlgorithm(std::vector<vec2>& points);

    //  assume that points are already sorted in the right order
    PUNK_ENGINE_API void CreateConvexHullFromSortedPoint(const std::vector<vec2>& points, std::vector<vec2>& result);
    PUNK_ENGINE_API void CreateConvexHull(std::vector<vec2> points, std::vector<vec2>& result);
}

#endif // GRAHAM_H
