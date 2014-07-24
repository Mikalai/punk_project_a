#ifndef _H_PUNK_FRUSTUM
#define _H_PUNK_FRUSTUM

#include "config.h"
#include <core/iobject.h>
#include "forward.h"

PUNK_ENGINE_BEGIN
namespace Math {

	DECLARE_PUNK_GUID(IID_IFrustum, "08ACEECF-36DC-42BB-A021-6DEF9B573141");
	DECLARE_PUNK_GUID(CLSID_Frustum, "EB481684-66C4-4BF9-B5FC-ABD034430671");

	class IFrustum : public Core::IObject {
	public:

		virtual const ClipSpace GetClipSpaceFromPoint(const point3d& p) const = 0;
		virtual const ClipSpace GetClipSpace() const = 0;
		virtual void SetPerspectiveProjectionMatrix(const Math::mat4& value) = 0;
		virtual const mat4 GetPerspectiveProjectionMatrix() const = 0;
		virtual const vec2 GetZRange(const Math::mat4& view) const = 0;
		virtual void Transform(const point3d &center, const vec3 &view_dir, const vec3 &_up) = 0;
		virtual void SetNearDistance(float znear) = 0;
		virtual void SetFarDistance(float zfar) = 0;
		virtual void SetFov(float fov) = 0;
		virtual void SetAspectRatio(float width, float height) = 0;
		virtual void SetAspectRatio(float aspect) = 0;
		virtual float GetFov() const = 0;
		virtual float GetFarDistance() const = 0;
		virtual float GetAspectRation() const = 0;
		virtual float GetNearDistance() const = 0;
	};
}
PUNK_ENGINE_END

#endif
