#include <math/curve.h>
#include "io_spline.h"
#include "io_curve.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveCurve(Core::Buffer* buffer, const Math::Curve& o)
    {
        buffer->WriteReal32(o.m_total_length);
        unsigned size = o.m_splines.size();
        buffer->WriteUnsigned32(size);
        for (auto& s : o.m_splines)
        {
            SaveSpline(buffer, s);
        }
    }

    void LoadCurve(Core::Buffer* buffer, Curve& o)
    {
        o.m_total_length = buffer->ReadReal32();
        unsigned size = buffer->ReadUnsigned32();
        o.m_splines.resize(size);
        for (auto& s : o.m_splines)
        {
            LoadSpline(buffer, s);
        }
    }
}
PUNK_ENGINE_END
