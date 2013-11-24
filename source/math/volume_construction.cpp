#include <algorithm>
#include "math_error.h"
#include "vec3.h"
#include "mat3.h"
#include "root_find.h"
#include "absolute_value.h"
#include "volume_construction.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            const vec3 CalculateAverage(const vec3* points, std::uint32_t count)
            {
                vec3 center;

                for (auto i = 0u; i < count; ++i)
                    center += points[i];

                center /= (float)count;

                return center;
            }

            const mat3 CreateCovarianceMatrix(const vec3* points, std::uint32_t count)
            {
                //	find average of the vertices
                vec3 center = CalculateAverage(points, count);

                //	find covariance matrix
                mat3 res;
                res.Zerofy();

                for (auto i = 0u; i < count; ++ i)
                {
                    res += MultTransposed((points[i] - center), (points[i] - center));
                }

                res /= (float)count;

                return res;
            }

            void DiagonalizeMatrix(const mat3& m, mat3& res)
            {
                vec3 v;
                EigenValues(m, v);
                res.Identity();
                res[0] = v[0];
                res[4] = v[1];
                res[8] = v[2];
            }

            void EigenValues(const mat3& m, vec3& res)
            {
                double a = double(1);
                double b = -(m[0] + m[4] + m[8]);
                double c = (m[0]*m[4] + m[0]*m[8] + m[4]*m[8] - m[7]*m[5] - m[1]*m[3] - m[2]*m[6]);
                double d = -(m[0]*m[4]*m[8] - m[0]*m[7]*m[5] - m[1]*m[3]*m[8] + m[1]*m[6]*m[5] + m[2]*m[3]*m[7] - m[2]*m[6]*m[4]);

                double in[] = {d, c, b, a};
                double out[3];
                auto result = SolveCubic(in, out);
                if (result == RootFindResult::RESULT_NO_SOLUTION)
                    throw Error::EigenValuesNotFound(0);
                std::sort(out, out+3);
                res[0] = (float)out[2];
                res[1] = (float)out[1];
                res[2] = (float)out[0];
            }

            void EigenVectors(const mat3& m, const vec3& value, vec3 res[3])
            {
                for (int v = 0; v < 3; ++v)
                {
                    //	use inverse power method
                    vec3 bb0(1,1,1);
                    vec3 bb = bb0;
                    float d;
                    do
                    {
                        bb0 = bb;
                        bb = (m - (value[v] + 0.001f) * mat3::CreateIdentity()).Inversed() * bb;
                        bb.Normalize();
                        d = fabs(fabs(bb.Dot(bb0)) - 1.0f);
                    }
                    while (d > 1e-5);

                    res[v] = bb;
                }
            }

            void SymmetricEigenSystem(const mat3& m, vec3& value, mat3& r)
            {
                const int max_sweep = 32;
                const float epsilon = 1.0e-10f;
                float m11 = m.At(0,0);
                float m12 = m.At(0,1);
                float m13 = m.At(0,2);
                float m22 = m.At(1,1);
                float m23 = m.At(1,2);
                float m33 = m.At(2,2);

                r.Identity();

                for (int a = 0; a < max_sweep; ++a)
                {
                    if ((Abs(m12) < epsilon) && (Abs(m13) < epsilon) && (Abs(m23) < epsilon))
                        break;

                    //	annihilate 1 2
                    if (m12 != 0.0f)
                    {
                        float u = (m22 - m11) * 0.5f / m12;
                        float u2 = u*u;
                        float u2p1 = u2 + 1.0f;
                        float t = (u2p1 != u2) ? ((u < 0.0f) ? -1.0f : 1.0f) * (sqrt(u2p1) - fabs(u)) : 0.5f / u;
                        float c = 1.0f / sqrt(t*t + 1.0f);
                        float s = c * t;

                        m11 -= t * m12;
                        m22 += t * m12;
                        m12 = 0.0f;

                        float temp = c*m13 - s * m23;
                        m23 = s * m13 + c * m23;
                        m13 = temp;

                        for (int i = 0; i < 3; ++i)
                        {
                            float temp = c * r.At(i, 0) - s * r.At(i,1);
                            r.At(i,1) = s * r.At(i,0) + c * r.At(i,1);
                            r.At(i,0) = temp;
                        }
                    }

                    //	annihilate 1 3
                    if (m13 != 0.0f)
                    {
                        float u = (m33 - m11) * 0.5f / m13;
                        float u2 = u*u;
                        float u2p1 = u2 + 1.0f;
                        float t = (u2p1 != u2) ? ((u < 0.0f) ? -1.0f : 1.0f) * (sqrt(u2p1) - fabs(u)) : 0.5f / u;
                        float c = 1.0f / sqrt(t*t + 1.0f);
                        float s = c * t;

                        m11 -= t * m13;
                        m33 += t * m13;
                        m13 = 0.0f;

                        float temp = c * m12 - s * m23;
                        m23 = s * m12 + c * m23;
                        m12 = temp;

                        for (int i = 0; i < 3; ++i)
                        {
                            float temp = c * r.At(i, 0) - s * r.At(i, 2);
                            r.At(i, 2) = s * r.At(i, 0) + c * r.At(i, 2);
                            r.At(i, 0) = temp;
                        }
                    }

                    //	annihilate 2 3
                    if (m23 != 0.0f)
                    {
                        float u = (m33 - m22) * 0.5f / m23;
                        float u2 = u*u;
                        float u2p1 = u2 + 1.0f;
                        float t = (u2p1 != u2) ? ((u < 0.0f) ? -1.0f : 1.0f) * (sqrt(u2p1) - fabs(u)) : 0.5f / u;
                        float c = 1.0f / sqrt(t*t + 1.0f);
                        float s = c * t;

                        m22 -= t * m23;
                        m33 += t * m23;
                        m23 = 0.0f;

                        float temp = c * m12 - s * m13;
                        m13 = s * m12 + c * m13;
                        m12 = temp;

                        for (int i = 0; i < 3; ++i)
                        {
                            float temp = c * r.At(i, 1) - s * r.At(i, 2);
                            r.At(i, 2) = s * r.At(i, 1) + c * r.At(i, 2);
                            r.At(i, 1) = temp;
                        }
                    }
                }
                value.Set(m11, m22, m33);
            }

            void CalculateNativeAxis(const vec3* points, std::uint32_t count, vec3& r, vec3& s, vec3& t)
            {
                //	find covariance matrix
                mat3 c = CreateCovarianceMatrix(points, count);

                //	find eigen values of the covariance matrix
                Math::vec3 eigen_values;
                EigenValues(c, eigen_values);

                //	find eigen vectors of the covariance matrix
                Math::vec3 eigen_vectors[3];
                EigenVectors(c, eigen_values, eigen_vectors);

                r = eigen_vectors[0];
                s = eigen_vectors[1];
                t = eigen_vectors[2];

                mat3 a;
                a.SetColumn(0, r);
                a.SetColumn(1, s);
                a.SetColumn(2, t);
            }
        }
    }
}
