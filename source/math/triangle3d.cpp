//#include <limits>
//#include "min_max.h"
//#include "triangle3d.h"
//#include "triangle2d.h"
//#include "line3d.h"
//
//namespace Punk {
//    namespace Engine {
//        namespace Math {
//
//            Triangle3D::Triangle3D()
//            {}
//
//            Triangle3D::Triangle3D(const vec3& v0, const vec3& v1, const vec3& v2)
//            {
//                m_v[0] = v0; m_v[1] = v1; m_v[2] = v2;
//                m_bbox.MinPoint().X() = Min(v0.X(), v1.X(), v2.X());
//                m_bbox.MinPoint().Y() = Min(v0.Y(), v1.Y(), v2.Y());
//                m_bbox.MinPoint().Z() = Min(v0.Z(), v1.Z(), v2.Z());
//                m_bbox.MaxPoint().X() = Max(v0.X(), v1.X(), v2.X());
//                m_bbox.MaxPoint().Y() = Max(v0.Y(), v1.Y(), v2.Y());
//                m_bbox.MaxPoint().Z() = Max(v0.Z(), v1.Z(), v2.Z());
//                m_normal = (v1 - v0).Cross(v2 - v0);
//                m_normal.Normalize();
//                m_distance = -m_normal.Dot(v0);
//            }
//
//        }
//    }
//}
