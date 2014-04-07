#include <math/weighted_point.h>
#include "io_vector.h"
#include "io_weighted_point.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveWeightedPoint(Core::Buffer* buffer, const Math::WeightedPoint& value)
    {
        buffer->WriteReal32(value.GetWeight());
        SaveVector4f(buffer, value.GetPoint());
    }

    void LoadWeightedPoint(Core::Buffer* buffer, Math::WeightedPoint& value)
    {
        value.SetWeight(buffer->ReadReal32());
        Math::vec4 point;
        LoadVector4f(buffer, point);
        value.SetPoint(point);
    }
}
PUNK_ENGINE_END
