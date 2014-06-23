#ifndef _H_PUNK_MATH_CLIP_SPACE
#define _H_PUNK_MATH_CLIP_SPACE

#include <cstdint>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            namespace __private {
                struct ClipSpaceImpl;
            }

            class Plane;

            class PUNK_ENGINE_API ClipSpace
            {
            public:
                ClipSpace();
                ClipSpace(const ClipSpace& value);
                ClipSpace& operator = (const ClipSpace& value);
                ~ClipSpace();

                void Add(const Plane& plane);
                std::size_t GetSize() const;
                bool Empty() const;
                const Plane& operator[] (std::size_t index) const;
                Plane& operator[] (std::size_t index);

                __private::ClipSpaceImpl* impl {nullptr};
            };
        }
    }
}

#endif
