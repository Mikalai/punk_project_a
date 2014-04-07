#include <ai/curvepath.h>
#include "io_string.h"
#include "io_object.h"
#include "io_curve.h"
#include "io_curve_path.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    void SaveCurvePath(Core::Buffer *buffer, const Core::Object *o)
    {
        SaveObject(buffer, o);
        const AI::CurvePath* p = Cast<const AI::CurvePath*>(o);
        SaveCurve(buffer, *p);
        SaveString(buffer, p->GetName());
    }

    void LoadCurvePath(Core::Buffer *buffer, Core::Object *o)
    {
        LoadObject(buffer, o);
        AI::CurvePath* p = Cast<AI::CurvePath*>(o);
        LoadCurve(buffer, *p);
        Core::String value;
        LoadString(buffer, value);
        p->SetName(value);
    }
}
PUNK_ENGINE_END
