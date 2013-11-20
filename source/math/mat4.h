#ifndef _H_MAT4X4_MATH
#define _H_MAT4X4_MATH

#include <initializer_list>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Core {
            class String;
        }

        namespace Math {

            class FrustumCore;
            class quat;
            class vec3;
            class vec2;
            class vec4;
            class mat3;

            class PUNK_ENGINE_API mat4
            {
            public:
                mat4();
                mat4(const mat4& m);
                mat4(float a0, float a1, float a2, float a3,
                     float a4, float a5, float a6, float a7,
                     float a8, float a9, float a10, float a11,
                     float a12, float a13, float a14, float a15);
                mat4(std::initializer_list<float> v);
                const mat4 Inversed() const;
                const mat3 RotationPart() const;
                const mat4 RotationPart4x4() const;
                const vec3 TranslationPart() const;
                float& operator [] (int i);
                const float& operator [] (int i) const;
                void SetColumn(int column, const vec4& v);
                void SetRow(int row, const vec4& v);
                const vec4 GetRow(int row) const;
                const vec4 GetColumn(int column) const;
                const mat4 Identity();
                const mat4 Transposed() const;
                const Core::String ToString() const;
                mat4& operator *= (const mat4& b);


                static const mat4 CreateTargetCameraMatrix(const vec3& eye, const vec3& target, const vec3& up);
                static const mat4 CreateFreeCameraMatrix(const vec3& eye, const vec3& dir, const vec3& up);
                static const mat4 CreatePerspectiveProjection(float fovy, float width, float height, float znear, float zfar);
                static const mat4 CreateOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far);
                static const mat4 CreateOrthographicProjection2(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
                static const mat4 CreateTextureBiasMatrix();
                static const mat4 CreateCropMatrix(const Math::FrustumCore &frustum, const Math::mat4 &shadow_view, const Math::mat4& shadow_proj, float& min_x, float& max_x, float& min_y, float& max_y);
                static const mat4 CreateLightProjectionMatrix(const Math::vec2& z_range);
                static const mat4 CreateFromQuaternion(const quat& value);
                static const mat4 CreateFromPoistionAndDirection(const Math::vec3& position, const Math::vec3& direction);
                static const mat4 CreatePerspectiveProjectionInfinity(float left, float right, float top, float bottom, float znear);
                static const mat4 CreatePerspectiveProjection(float left, float right, float top, float bottom, float znear, float zfar);
                static const mat4 CreateIdentity();
                static const mat4 CreateScaling(float sx, float sy, float sz);
                static const mat4 CreateTranslate(float x, float y, float z);
                static const mat4 CreateTranslate(const vec3& v);
                static const mat4 CreateZRotation(float angle);
                static const mat4 CreateXRotation(float angle);
                static const mat4 CreateYRotation(float angle);
                static const mat4 CreateRotation(float x, float y, float z, float angle);
                static const mat4 CreateReflectZ();
                static const mat4 CreateReflectX();
                static const mat4 CreateReflectY();
                static const mat4 CreateFromYawPitchRoll(const vec3& eye, float yaw, float pitch, float roll);

            private:
                float m[16];
            };

            PUNK_ENGINE_API const mat4 operator + (const mat4& a, const mat4& b);
            PUNK_ENGINE_API const mat4 operator * (const mat4& a, const mat4& b);
            PUNK_ENGINE_API const vec4 operator * (const mat4& m, const vec4& v);
            PUNK_ENGINE_API const vec3 operator * (const mat4& m, const vec3& v);
            PUNK_ENGINE_API const mat4 operator * (const mat4& m, const float& v);
            PUNK_ENGINE_API const mat4 operator * (const float& v, const mat4& m);
            PUNK_ENGINE_API bool operator == (const mat4& l, const mat4& r);
            PUNK_ENGINE_API bool operator != (const mat4& l, const mat4& r);
        }
    }
}

#endif  //  _H_MAT4X4_MATH
