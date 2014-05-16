#ifndef _H_PUNK_CAMERA
#define _H_PUNK_CAMERA

#include <config.h>
#include <core/object.h>
#include <math/mat4.h>
#include <math/line3d.h>
#include <math/frustum.h>
#include <math/constants.h>
#include <math/rect.h>

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class ICamera : public virtual Core::IObject
	{
	public:		
        const Math::mat4 GetProjectionMatrix();
		const Math::mat4 GetViewMatrix() const;
		const Math::vec3 GetDirection() const { return m_direction; }
		const Math::vec3 GetUpVector() const { return m_up; }
		const Math::ClipSpace ToClipSpace() const;        

		void SetYaw(float value);
		void SetRoll(float value);
		void SetPitch(float value);

		void SetYawRollPitch(float yaw, float roll, float pitch);
		void SetYawRollPitch(const Math::vec3& yrp);

		const Math::vec3& GetYawRollPitch() const { return m_yrp; }
		float GetYaw() const { return m_yrp[0]; }
		float GetRoll() const { return m_yrp[1]; }
		float GetPitch() const { return m_yrp[2]; }

		const Math::vec3& GetRightVector() const { return m_right; }

        Math::FrustumCore& GetFrustum() { return m_frustum; }
        const Math::FrustumCore& GetFrustum() const { return m_frustum; }

		const Math::Rect& GetViewport() const { return m_viewport; }
		void SetViewport(float x, float y, float width, float height) { m_viewport.Set(x, y, width, height); }

		const Math::Line3D GetWorldRay(float view_x, float view_y);
	private:
		Math::vec3 m_yrp;	//	yaw roll pitch
		Math::vec3 m_position;
		Math::vec3 m_direction;
		Math::vec3 m_right;
		Math::vec3 m_up;
		Math::mat4 m_view_matrix;
        Math::mat4 m_proj_matrix;
        Math::FrustumCore m_frustum;
		Math::Rect m_viewport;

		void UpdateInternals();

        PUNK_OBJECT_DEFAULT_IMPL(Camera)
	};    
}
PUNK_ENGINE_END

#endif
