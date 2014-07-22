#ifndef _H_STAT_MATH
#define _H_STAT_MATH

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T, int Dim, typename tag>
    const Tuple<T, Dim, tag> CalculateAverage(const std::vector<Tuple<T, Dim, tag>>& points)
    {
        Tuple<T, Dim, tag> center;

        for (auto i = 0u; i < points.size(); ++i)
            center += points[i];

        center /= (T)points.size();

        return center;
    }
}
PUNK_ENGINE_END

#endif //   _H_STAT_MATH
