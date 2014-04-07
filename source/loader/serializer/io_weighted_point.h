#ifndef IO_WEIGHTED_POINT_H
#define IO_WEIGHTED_POINT_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core {
    class Buffer;
}
namespace Math {
    class WeightedPoint;
}
namespace Loader {
    void SaveWeightedPoint(Core::Buffer* buffer, const Math::WeightedPoint& value);
    void LoadWeightedPoint(Core::Buffer* buffer, Math::WeightedPoint& value);
}
PUNK_ENGINE_END

#endif // IO_WEIGHTED_POINT_H
