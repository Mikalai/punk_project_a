#ifndef _H_PUNK_CAMERA
#define _H_PUNK_CAMERA

#include <config.h>
#include <core/iobject.h>
#include <math/ifrustum.h>
#include "ioptics.h"

PUNK_ENGINE_BEGIN
namespace System {
	class IWindow;
}
namespace Attributes
{
	DECLARE_PUNK_GUID(IID_ICamera, "C709623C-A93F-4BA5-B0EC-8B9E7BC60283");
	DECLARE_PUNK_GUID(IID_ICamera2, "6D79583B-0A72-42DA-A638-560CD6B9916E");
	DECLARE_PUNK_GUID(CLSID_Camera2, "4634EA6B-F9E2-4681-A5C8-5F5803D18400");

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

	class ICamera2 : public Core::IObject {
	public:
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetId() const = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;
		virtual void SetOptics(IOpticsPtr value) = 0;
		virtual IOpticsPtr GetOptics() const = 0;
	};

	using ICamera2Ptr = Core::Pointer < ICamera2 > ;

	inline ICamera2Ptr NewCamera2() {
		return System::CreateInstancePtr<ICamera2>(CLSID_Camera2, IID_ICamera2);
	}
}
PUNK_ENGINE_END

#endif
