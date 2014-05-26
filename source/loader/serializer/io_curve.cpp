//#include <string/module.h>
//#include <math/curve.h>
//#include "io_spline.h"
//#include "io_curve.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule {
//    void SaveCurve(Core::Buffer* buffer, const Math::Curve& o)
//    {
//        unsigned size = o.GetSplines().size();
//        buffer->WriteUnsigned32(size);
//        for (auto& s : o.GetSplines())
//        {
//            SaveSpline(buffer, s);
//        }
//    }
//
//    void LoadCurve(Core::Buffer* buffer, Math::Curve& o)
//    {
//        o.Clear();
//        unsigned size = buffer->ReadUnsigned32();
//        Math::Curve::Splines splines(size);
//        for (auto& s : splines)
//        {
//            LoadSpline(buffer, s);
//        }
//        o.AddSplines(splines);
//    }
//}
//PUNK_ENGINE_END
