#include "aabb.h"
#include "line3d.h"
#include <algorithm>
#include <limits>

namespace Punk {
    namespace Engine {
        namespace Math {

            void AxisAlignedBox::Create(const float* data, unsigned offset, int count)
            {
                unsigned off = offset/sizeof(float);
                m_min[0] = m_max[0] = data[0];
                m_min[1] = m_max[1] = data[1];
                m_min[2] = m_max[2] = data[2];
                for (int i = 0; i < count; i ++)
                {
                    if (m_min[0] > *(data + i*off + 0))
                        m_min[0] = *(data + i*off + 0);
                    if (m_min[1] > *(data + i*off + 1))
                        m_min[1] = *(data + i*off + 1);
                    if (m_min[2] > *(data + i*off + 2))
                        m_min[2] = *(data + i*off + 2);
                    if (m_max[0] < *(data + i*off + 0))
                        m_max[0] = *(data + i*off + 0);
                    if (m_max[1] < *(data + i*off + 1))
                        m_max[1] = *(data + i*off + 1);
                    if (m_max[2] < *(data + i*off + 2))
                        m_max[2] = *(data + i*off + 2);
                }
            }

            AxisAlignedBox Merge(const AxisAlignedBox* b1, const AxisAlignedBox* b2)
            {
                AxisAlignedBox res;
                res.MinPoint()[0] = b1->MinPoint()[0] < b2->MinPoint()[0] ? b1->MinPoint()[0] : b2->MinPoint()[0];
                res.MinPoint()[1] = b1->MinPoint()[1] < b2->MinPoint()[1] ? b1->MinPoint()[1] : b2->MinPoint()[1];
                res.MinPoint()[2] = b1->MinPoint()[2] < b2->MinPoint()[2] ? b1->MinPoint()[2] : b2->MinPoint()[2];

                res.MaxPoint()[0] = b1->MaxPoint()[0] > b2->MaxPoint()[0] ? b1->MaxPoint()[0] : b2->MaxPoint()[0];
                res.MaxPoint()[1] = b1->MaxPoint()[1] > b2->MaxPoint()[1] ? b1->MaxPoint()[1] : b2->MaxPoint()[1];
                res.MaxPoint()[2] = b1->MaxPoint()[2] > b2->MaxPoint()[2] ? b1->MaxPoint()[2] : b2->MaxPoint()[2];

                return res;
            }

            const vec3& AxisAlignedBox::MinPoint() const
            {
                return m_min;
            }

            const vec3& AxisAlignedBox::MaxPoint() const
            {
                return m_max;
            }

            vec3& AxisAlignedBox::MinPoint()
            {
                return m_min;
            }

            vec3& AxisAlignedBox::MaxPoint()
            {
                return m_max;
            }

            void AxisAlignedBox::Set(const vec3& min_point, const vec3& max_point)
            {
                m_min = max_point;
                m_max = min_point;
            }
        }
    }
}
