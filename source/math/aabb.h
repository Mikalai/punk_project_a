#ifndef _H_PUNK_MATH_AABB
#define _H_PUNK_MATH_AABB

#include "config.h"
#include "vec3.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            class mat4;

            class PUNK_ENGINE_API AxisAlignedBox
            {
            public:

                void Create(const float* data, unsigned offset, int count);

                const vec3& MinPoint() const;
                const vec3& MaxPoint() const;
                vec3& MinPoint();
                vec3& MaxPoint();

                void Set(const vec3& min_point, const vec3& max_point);

            private:
                vec3 m_min;
                vec3 m_max;
            };

            PUNK_ENGINE_API AxisAlignedBox Merge(const AxisAlignedBox* b1, const AxisAlignedBox* b2);
        }
    }
}

#endif	//	_H_PUNK_MATH_AABB
