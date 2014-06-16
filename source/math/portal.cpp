#include <vector>
#include "vec3.h"
#include "mat4.h"
#include "plane.h"
#include "portal.h"
#include "math_error.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            namespace __private {
                struct PortalImpl {
                    std::vector<vec3> m_points;
                    Plane m_plane;
                };
            }

            Portal::Portal()
                : impl(new __private::PortalImpl) {}

            Portal::Portal(const Portal &value)
                : impl(new __private::PortalImpl(*value.impl)) {}

            Portal& Portal::operator = (const Portal& value) {
                Portal temp(value);
                std::swap(impl, temp.impl);
                return *this;
            }

            Portal::~Portal() {
                delete impl;
                impl = nullptr;
            }

            bool Portal::SetPoints(const vec3* points, std::uint32_t count)
            {
                if (count < 3)
                    throw Error::NotEnoughData(0);

                impl->m_points.resize(count);
                for (auto i = 0u; i < count; ++i)
                    impl->m_points[i] = points[i];

                const vec3& p0 = impl->m_points[0];
                const vec3& p1 = impl->m_points[1];
                const vec3& p2 = impl->m_points[2];

                impl->m_plane.Set(p0, p1, p2);

                return true;
            }

            const Portal operator * (const mat4& m, const Portal& p)
            {
                Portal result;
                result.SetSize(p.GetSize());
                for (auto i = 0u; i < p.GetSize(); ++i) {
                    result[i] = m*p[i];
                }
                return result;
            }

            const vec3 Portal::GetNormal() const {
                return impl->m_plane.GetNormal();
            }

            float Portal::GetDistance() const {
                return impl->m_plane.GetDistance();
            }

            std::uint32_t Portal::GetSize() const {
				return (std::uint32_t)impl->m_points.size();
            }

            void Portal::SetSize(std::uint32_t value) {
                impl->m_points.resize(value);
            }

            vec3& Portal::operator [] (std::uint32_t index) {
                return impl->m_points[index];
            }

            const vec3& Portal::operator [] (std::uint32_t index) const {
                return impl->m_points[index];
            }

            //    void SaveBoundingBox(Core::Buffer *buffer, const Portal& value)
            //    {
            //        if (value.m_points.empty())
            //            throw System::PunkException("Can't save bad portal");

            //        int size = (int)value.m_points.size();
            //        buffer->WriteSigned32(size);
            //        for (auto& p : value.m_points)
            //            SaveVector3f(buffer, p);
            //        SavePlane(buffer, value.m_plane);
            //    }

            //    void LoadBoundingBox(Core::Buffer *buffer, Portal& value)
            //    {
            //        int size = buffer->ReadSigned32();
            //        value.m_points.resize(size);
            //        for (auto& p : value.m_points)
            //            LoadVector3f(buffer, p);
            //        LoadPlane(buffer, value.m_plane);
            //    }
        }
    }
}
