#include "bounding_sphere.h"
#include "volume_construction.h"
#include "math_error.h"
#include "vec3.h"
#include "mat4.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            const BoundingSphere operator * (const mat4& m, const BoundingSphere& bsphere)
            {
                BoundingSphere res;
                //  mat4 plane_matrix = m.Inversed().Transposed();
                //	mat3 normal_matrix = plane_matrix.RotationPart();

                res.SetCenter(m * bsphere.GetCenter());
                res.SetRadius(bsphere.GetRadius());
                return res;
            }

            void BoundingSphere::Create(const vec3 *points, std::uint32_t count)
            {
                if (count == 0 || points == nullptr)
                    throw Error::NotEnoughData(0);

                vec3 r, s, t;
                CalculateNativeAxis(points, count, r, s, t);

                vec3 min_p = points[0];
                float min_value = r.Dot(min_p);
                vec3 max_p = min_p;
                float max_value = r.Dot(max_p);

                for (auto i = 0u; i < count; ++i)
                {
                    float value = r.Dot(points[i]);
                    if (min_value > value)
                    {
                        min_p = points[i];
                        min_value = value;
                    }

                    if (max_value < value)
                    {
                        max_p = points[i];
                        max_value = value;
                    }
                }

                const vec3 q = (min_p + max_p) / 2.0f;
                float radius = (min_p - q).Length();

                SetCenter(q);
                SetRadius(radius);
            }

            //    void SaveBoundingSphere(System::Buffer* buffer, const BoundingSphere& sphere)
            //    {
            //        SaveSphere(buffer, sphere);
            //    }

            //    void LoadBoundingSphere(System::Buffer* buffer, BoundingSphere& sphere)
            //    {
            //        LoadSphere(buffer, sphere);
            //    }
        }
    }
}
