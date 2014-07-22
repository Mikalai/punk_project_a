//#include <vector>
//#include "vec3.h"
//#include "mat4.h"
//#include "plane.h"
//#include "portal.h"
//#include "math_error.h"

//namespace Punk {
//    namespace Engine {
//        namespace Math {
//            namespace __private {
//                struct PortalImpl {

//                };
//            }

//            Portal::Portal()
//                : impl(new __private::PortalImpl) {}

//            Portal::Portal(const Portal &value)
//                : impl(new __private::PortalImpl(*value.impl)) {}

//            Portal& Portal::operator = (const Portal& value) {
//                Portal temp(value);
//                std::swap(impl, temp.impl);
//                return *this;
//            }

//            Portal::~Portal() {
//                delete impl;
//                impl = nullptr;
//            }







//            //    void SaveBoundingBox(Core::Buffer *buffer, const Portal& value)
//            //    {
//            //        if (value.m_points.empty())
//            //            throw System::PunkException("Can't save bad portal");

//            //        int size = (int)value.m_points.size();
//            //        buffer->WriteSigned32(size);
//            //        for (auto& p : value.m_points)
//            //            SaveVector3f(buffer, p);
//            //        SavePlane(buffer, value.m_plane);
//            //    }

//            //    void LoadBoundingBox(Core::Buffer *buffer, Portal& value)
//            //    {
//            //        int size = buffer->ReadSigned32();
//            //        value.m_points.resize(size);
//            //        for (auto& p : value.m_points)
//            //            LoadVector3f(buffer, p);
//            //        LoadPlane(buffer, value.m_plane);
//            //    }
//        }
//    }
//}
