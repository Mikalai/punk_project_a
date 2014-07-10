#ifndef _H_IPERSPECTIVE_CAMERA
#define _H_IPERSPECTIVE_CAMERA

#include "icamera.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IPerspectiveCamera, "13309930-833F-4783-9B16-6F10DF01C8B4");
	DECLARE_PUNK_GUID(CLSID_PerspectiveCamera, "0675F012-041E-4AB9-9FD9-E26688FD4E14");

	class IPerspectiveCamera : public ICamera {
	public:
		virtual void SetFieldOfView(float angle) = 0;
		virtual void SetNearClipPlane(float value) = 0;
		virtual void SetFarClipPlane(float value) = 0;
		virtual float GetFieldOfView() const = 0;
		virtual float GetNearClipPlane() const = 0;
		virtual float GetFarClipPlane() const = 0;
		virtual const Math::Frustum GetFrustum() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IPERSPECTIVE_CAMERA