#ifndef MATRIX_HELPER_H
#define MATRIX_HELPER_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {
    class vec2;
    class vec3;
    class quat;
    class mat4;
    class FrustumCore;

	PUNK_ENGINE_API const mat4 CreatePositionRotationScaleMatrix(const Math::vec3& position, const Math::quat& rotation, const Math::vec3& scale);
    PUNK_ENGINE_API const mat4 CreateTargetCameraMatrix(const vec3& eye, const vec3& target, const vec3& up);
    PUNK_ENGINE_API const mat4 CreateFreeCameraMatrix(const vec3& eye, const vec3& dir, const vec3& up);
    PUNK_ENGINE_API const mat4 CreatePerspectiveProjection(float fovy, float width, float height, float znear, float zfar);
    PUNK_ENGINE_API const mat4 CreateOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far);
    PUNK_ENGINE_API const mat4 CreateOrthographicProjection2(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
    PUNK_ENGINE_API const mat4 CreateTextureBiasMatrix();
    PUNK_ENGINE_API const mat4 CreateCropMatrix(const Math::FrustumCore &frustum, const Math::mat4 &shadow_view, const Math::mat4& shadow_proj, float& min_x, float& max_x, float& min_y, float& max_y);
    PUNK_ENGINE_API const mat4 CreateLightProjectionMatrix(const Math::vec2& z_range);
    PUNK_ENGINE_API const mat4 CreateFromQuaternion(const quat& value);
    PUNK_ENGINE_API const mat4 CreateFromPoistionAndDirection(const Math::vec3& position, const Math::vec3& direction);
    PUNK_ENGINE_API const mat4 CreatePerspectiveProjectionInfinity(float left, float right, float top, float bottom, float znear);
    PUNK_ENGINE_API const mat4 CreatePerspectiveProjection(float left, float right, float top, float bottom, float znear, float zfar);
    PUNK_ENGINE_API const mat4 CreateIdentity();
    PUNK_ENGINE_API const mat4 CreateScaling(float sx, float sy, float sz);
	PUNK_ENGINE_API const mat4 CreateScaling(const Math::vec3& value);
    PUNK_ENGINE_API const mat4 CreateTranslate(float x, float y, float z);
    PUNK_ENGINE_API const mat4 CreateTranslate(const vec3& v);
    PUNK_ENGINE_API const mat4 CreateZRotation(float angle);
    PUNK_ENGINE_API const mat4 CreateXRotation(float angle);
    PUNK_ENGINE_API const mat4 CreateYRotation(float angle);
    PUNK_ENGINE_API const mat4 CreateRotation(float x, float y, float z, float angle);
    PUNK_ENGINE_API const mat4 CreateReflectZ();
    PUNK_ENGINE_API const mat4 CreateReflectX();
    PUNK_ENGINE_API const mat4 CreateReflectY();
    PUNK_ENGINE_API const mat4 CreateFromYawPitchRoll(const vec3& eye, float yaw, float pitch, float roll);
}
PUNK_ENGINE_END

#endif // MATRIX_HELPER_H
