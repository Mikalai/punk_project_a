#include <math.h>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "quat.h"
#include "frustum.h"
#include "matrix_helper.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            const mat4 CreatePerspectiveProjection(float fovy,
                                                   float width,
                                                   float height,
                                                   float znear,
                                                   float zfar) {
                mat4 res;

                float f = 1.0f / tanf(0.5f * fovy);
                float aspect = width / height;
                float* m = &res[0];

                m[0*4 + 0] = f / aspect;
                m[0*4 + 1] = 0.0f;
                m[0*4 + 2] = 0.0f;
                m[0*4 + 3] = 0.0f;

                m[1*4 + 0] = 0.0f;
                m[1*4 + 1] = f;
                m[1*4 + 2] = 0.0f;
                m[1*4 + 3] = 0.0f;

                m[2*4 + 0] = 0.0f;
                m[2*4 + 1] = 0.0f;
                m[2*4 + 2] = (zfar + znear) / (znear - zfar);
                m[2*4 + 3] = -1.0f;

                m[3*4 + 0] = 0.0f;
                m[3*4 + 1] = 0.0f;
                m[3*4 + 2] = (2.0f * zfar * znear) / (znear - zfar);
                m[3*4 + 3] = 0.0f;

                return res;
            }

            const mat4 CreateTargetCameraMatrix(const vec3& _eye, const vec3& _target, const vec3& _up) {
                vec3 F = (_target - _eye);
                vec3 f = F.Normalized();

                vec3 up = _up.Normalized();
                vec3 s = f.Cross(up).Normalized();
                vec3 u = s.Cross(f);

                mat4 m;
                m[0*4 + 0] = s[0];
                m[1*4 + 0] = s[1];
                m[2*4 + 0] = s[2];
                m[3*4 + 0] = 0;

                m[0*4 + 1] = u[0];
                m[1*4 + 1] = u[1];
                m[2*4 + 1] = u[2];
                m[3*4 + 1] = 0;

                m[0*4 + 2] = -f[0];
                m[1*4 + 2] = -f[1];
                m[2*4 + 2] = -f[2];
                m[3*4 + 2] = 0;

                m[0*4 + 3] = 0.0f;
                m[1*4 + 3] = 0.0f;
                m[2*4 + 3] = 0.0f;
                m[3*4 + 3] = 1.0f;/**/
                m = m * CreateTranslate(-_eye.X(), -_eye.Y(), -_eye.Z());
                return m;
            }

            const mat4 CreateFreeCameraMatrix(const vec3& eye, const vec3& dir, const vec3& up) {
                return CreateTargetCameraMatrix(eye, eye + dir, up);
            }

            const mat4 CreateTranslate(float x, float y, float z) {
                mat4 m;
                m[12] = x;
                m[13] = y;
                m[14] = z;
                return m;
            }

            const mat4 CreateTranslate(const vec3 &v) {
                return CreateTranslate(v[0], v[1], v[2]);
            }

            const mat4 CreateOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far)
            {
                mat4 res;

                float tx = - (right + left) / (right - left);
                float ty = - (top + bottom) / (top - bottom);
                float tz = - (_far + _near) / (_far - _near);

                res[0] = 2.0f / (right - left);
                res[1] = 0;
                res[2] = 0;
                res[3] = 0;

                res[4] = 0;
                res[5] = 2.0f / (top - bottom);
                res[6] = 0;
                res[7] = 0;

                res[8] = 0;
                res[9] = 0;
                res[10] = -2.0f / (_far - _near);
                res[11] = 0;

                res[12] = tx;
                res[13] = ty;
                res[14] = tz;
                res[15] = 1;

                return res;
            }

            const mat4 CreateOrthographicProjection2(float xmin, float xmax, float ymin, float ymax, float, float zmax)
            {
                Math::mat4 m;
                m[0] = 2.0 / (xmax - xmin);
                m[1] = 0;
                m[2] = 0;
                m[3] = 0;

                m[4] = 0;
                m[5] = 2.0 / (ymax - ymin);
                m[6] = 0;
                m[7] = 0;

                m[8] = 0;
                m[9] = 0;
                m[10] = -2.0 / zmax;
                m[11] = 0;

                m[12] = - (xmax + xmin) / (xmax - xmin);
                m[13] = - (ymax + ymin) / (ymax - ymin);
                m[14] = -1;
                m[15] = 1;
                return m;
            }

            const mat4 CreatePerspectiveProjectionInfinity(float left, float right, float top, float bottom, float znear) {
                mat4 res;
                res[0] = 2.0f*znear / (right - left);
                res[1] = res[2] = res[3] = res[4] = 0;
                res[5] = 2.0f*znear / (top - bottom);
                res[6] = res[7] = 0;
                res[8] = (right + left) / (right - left);
                res[9] = (top + bottom) / (top - bottom);
                res[10] = -1;
                res[11] = -1;
                res[12] = res[13] = 0;
                res[14] = -2.0f*znear;
                res[15] = 0;
                return res;
            }

            const mat4 CreateTextureBiasMatrix()
            {
                const float bias[16] = {	0.5f, 0.0f, 0.0f, 0.0f,
                                            0.0f, 0.5f, 0.0f, 0.0f,
                                            0.0f, 0.0f, 0.5f, 0.0f,
                                            0.5f, 0.5f, 0.5f, 1.0f	};
                Math::mat4 b;
                for (int i = 0; i != 16; ++i)
                {
                    b[i] = bias[i];
                }

                return b;
            }

            //            const Math::mat4 mat4::CreateCropMatrix(const Math::FrustumCore &frustum, const Math::mat4 &shadow_view, const Math::mat4& shadow_proj, float& min_x, float& max_x, float& min_y, float& max_y)
            //            {
            //                max_x = -std::numeric_limits<float>::infinity();
            //                min_x = std::numeric_limits<float>::infinity();
            //                max_y = -std::numeric_limits<float>::infinity();
            //                min_y = std::numeric_limits<float>::infinity();
            //                auto shadow_proj_view = shadow_proj * shadow_view;

            //                // find the extends of the frustum slice as projected in light's homogeneous coordinates
            //                for (int j = 0; j < 8; ++j)
            //                {
            //                    auto transf = shadow_proj_view * Math::vec4(frustum.point[j], 1.0f);
            //                    float x = transf.X() / transf.W();
            //                    float y = transf.Y() / transf.W();

            //                    if (x > max_x)
            //                        max_x = x;
            //                    if (x < min_x)
            //                        min_x = x;
            //                    if (y > max_y)
            //                        max_y = y;
            //                    if (y < min_y)
            //                        min_y = y;
            //                }

            //                float scaleX = 2.0f / (max_x - min_x);
            //                float scaleY = 2.0f / (max_y - min_y);
            //                float offsetX = -0.5f * (max_x + min_x) * scaleX;
            //                float offsetY = -0.5f * (max_y + min_y) * scaleY;

            //                Math::mat4 crop_matrix;
            //                crop_matrix[0] = scaleX;
            //                crop_matrix[1 * 4 + 1] = scaleY;
            //                crop_matrix[3] = offsetX;
            //                crop_matrix[1 * 4 + 3] = offsetY;
            //                crop_matrix = crop_matrix.Transposed();
            //                return crop_matrix;
            //            }

            const mat4 CreateLightProjectionMatrix(const Math::vec2& z_range)
            {
                // set the projection matrix with the new z-bounds
                // note the inversion because the light looks at the neg.
                auto projection = CreateOrthographicProjection2(-1.0, 1.0, -1.0, 1.0, -z_range[1], -z_range[0]);
                return projection;
            }

            const mat4 CreateFromQuaternion(const quat& q)
            {
                float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
                x2 = q.X() + q.X();
                y2 = q.Y() + q.Y();
                z2 = q.Z() + q.Z();
                xx = q.X() * x2;   xy = q.X() * y2;   xz = q.X() * z2;
                yy = q.Y() * y2;   yz = q.Y() * z2;   zz = q.Z() * z2;
                wx = q.W() * x2;   wy = q.W() * y2;   wz = q.W() * z2;
                mat4 mat;
                float* m = &mat[0];
                m[0]=1.0f-(yy+zz); m[1]=xy-wz;        m[2]=xz+wy; m[3] = 0;
                m[4]=xy+wz;        m[5]=1.0f-(xx+zz); m[6]=yz-wx; m[7] = 0;
                m[8]=xz-wy;        m[9]=yz+wx;        m[10]=1.0f-(xx+yy); m[11] = 0;
                m[12] = m[13] = m[14] = 0;
                m[15] = 1;

                return mat;
            }

            const mat4 CreateRotation(float x, float y, float z, float angle)
            {
                float inversed_length = 1.0f/sqrtf(x*x+y*y+z*z);

                x *= inversed_length;
                y *= inversed_length;
                z *= inversed_length;

                mat4 result;
                float c = cos(angle);
                float s = sin(angle);
                result.SetColumn(0, vec4(c+(1-c)*x*x, (1-c)*x*y+s*z, (1-c)*x*z-s*y, 0));
                result.SetColumn(1, vec4((1-c)*x*y-s*z, c+(1-c)*y*y, (1-c)*y*z+s*x, 0));
                result.SetColumn(2, vec4((1-c)*x*z+s*y, (1-c)*y*z-s*x, c+(1-c)*z*z, 0));
                result.SetColumn(3, vec4(0,0,0,1));
                return result;
            }

            const mat4 CreateIdentity()
            {
                return mat4();
            }
        }
    }
}
