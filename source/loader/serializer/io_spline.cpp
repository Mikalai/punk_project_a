//#include <string/module.h>
//#include <math/ispline.h>
//#include <math/weighted_point.h>
//#include "io_weighted_point.h"
//#include "io_spline.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule {
//    void SaveSpline(Core::Buffer* buffer, const Math::Spline& spline)
//    {
//        unsigned size = spline.GetTotalLength();
//        buffer->WriteUnsigned32(size);
//        for (int i = 0; i < (int)spline.GetPointsCount(); ++i)
//        {
//            SaveWeightedPoint(buffer, spline.GetPoint(i));
//        }
//    }
//
//    void LoadSpline(Core::Buffer* buffer, Math::Spline& spline)
//    {
//        unsigned size = buffer->ReadUnsigned32();
//        std::vector<Math::WeightedPoint> points(size);
//        for (auto& p : points)
//        {
//            LoadWeightedPoint(buffer, p);
//        }
//        spline.AddPoints(points);
//    }
//}
//PUNK_ENGINE_END
