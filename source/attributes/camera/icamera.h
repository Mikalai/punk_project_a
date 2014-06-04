#ifndef _H_PUNK_CAMERA
#define _H_PUNK_CAMERA

#include <config.h>
#include <core/iobject.h>
#include <math/mat4.h>
#include <math/line3d.h>
#include <math/frustum.h>
#include <math/constants.h>
#include <math/rect.h>

PUNK_ENGINE_BEGIN
namespace System {
	class IWindow;
}
namespace Attributes
{
	DECLARE_PUNK_GUID(IID_ICamera, "C709623C-A93F-4BA5-B0EC-8B9E7BC60283");

    class ICamera : public Core::IObject
	{
	public:		
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;
		virtual const Math::mat4 GetProjectionMatrix() const = 0;		
		virtual const Math::vec3 GetDirection() const = 0;
		virtual void SetDirection(const Math::vec3& value) = 0;
		virtual const Math::vec3 GetUpVector() const = 0;
		virtual void SetUpVector(const Math::vec3& value) = 0;
		virtual const Math::ClipSpace GetClipSpace() const = 0;		
		virtual void BindToWindow(System::IWindow* window) = 0;
		virtual System::IWindow* GetWindow() const = 0;
		virtual const Math::vec2 GetZRange(const Math::mat4& view) const = 0;
	};    
}
PUNK_ENGINE_END

#endif
