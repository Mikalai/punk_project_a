#ifndef _H_STAT_MATH
#define _H_STAT_MATH

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T, int Dim, typename tag>
    const Tuple<T, Dim, tag> CalculateAverage(const Tuple<T, Dim, tag>* points, std::uint32_t count)
    {
        Tuple<T, Dim, tag> center;

        for (auto i = 0u; i < count; ++i)
            center += points[i];

        center /= (T)count;

        return center;
    }
}
PUNK_ENGINE_END

#endif //   _H_STAT_MATH
