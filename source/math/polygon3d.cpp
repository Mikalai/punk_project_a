#include <vector>
#include "vec3.h"
#include "polygon3d.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            namespace __private {
                struct Polygon3DImpl {
                    std::vector<vec3> m_points;
                    bool m_is_planar;
                };
            }

            Polygon3D::Polygon3D()
                : impl(new __private::Polygon3DImpl) {}

            Polygon3D::Polygon3D(const Polygon3D& value)
                : impl(new __private::Polygon3DImpl(*value.impl)) {}

            Polygon3D& Polygon3D::operator = (const Polygon3D& value) {
                Polygon3D temp(value);
                std::swap(impl, temp.impl);
                return *this;
            }

            Polygon3D::~Polygon3D() {
                delete impl;
                impl = nullptr;
            }

            void Polygon3D::Append(const vec3& p) {
                impl->m_points.push_back(p);
            }

            const vec3* Polygon3D::GetPoints() const {
                return &impl->m_points[0];
            }

            std::size_t Polygon3D::GetCount() const {
                return impl->m_points.size();
            }

            bool Polygon3D::IsPlanar() {
                return impl->m_is_planar;
            }

            bool Polygon3D::IsTriangle() {
                return impl->m_points.size() == 3;
            }

            //	modifies current polygon
            Polygon3D& Polygon3D::MakePlanar() {
                return *this;
            }
        }
    }
}
