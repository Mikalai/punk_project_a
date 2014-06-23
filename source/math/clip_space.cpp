#include <vector>
#include "plane.h"
#include "clip_space.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            namespace __private {
                struct ClipSpaceImpl {
                    std::vector<Plane> m_planes;
                };
            }

            ClipSpace::ClipSpace()
                : impl(new __private::ClipSpaceImpl) {}

            ClipSpace::ClipSpace(const ClipSpace &value)
                : impl(new __private::ClipSpaceImpl(*value.impl)) {}

            ClipSpace& ClipSpace::operator = (const ClipSpace& value) {
                ClipSpace temp(value);
                std::swap(impl, temp.impl);
                return *this;
            }

            ClipSpace::~ClipSpace() {
                delete impl;
                impl = nullptr;
            }

            void ClipSpace::Add(const Plane& plane) {
                impl->m_planes.push_back(plane);
            }

            std::size_t ClipSpace::GetSize() const {
                return impl->m_planes.size();
            }

            bool ClipSpace::Empty() const {
                return impl->m_planes.empty();
            }

            const Plane& ClipSpace::operator [] (std::size_t index) const {
                return impl->m_planes[index];
            }

            Plane& ClipSpace::operator [] (std::size_t index) {
                return impl->m_planes[index];
            }
        }
    }
}
