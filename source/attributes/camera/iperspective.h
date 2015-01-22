#ifndef _H_IPERSPECTIVE
#define _H_IPERSPECTIVE

#include <config.h>
#include <system/factory/interface.h>
#include <core/iobject.h>
#include <attributes/data_flow/ivalue.h>
#include <math/angle.h>
#include "iprojection.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IPerspective, "21A4A680-782D-4F9F-BF0B-8FF48F8B94F7");
	DECLARE_PUNK_GUID(CLSID_Perspective, "1DC91647-F8B7-4DED-951E-D773B0AFA05F");

	class IPerspective : public Core::IObject {
	public:
		virtual void SetFovX(const Math::radf& value) = 0;
		virtual const Math::radf& GetFovX() const = 0;
		virtual void SetFovY(const Math::radf& value) = 0;
		virtual const Math::radf& GetFovY() const = 0;
		virtual void SetAspectRatio(const Math::realf& value) = 0;
		virtual const Math::realf& GetAspectRatio() const = 0;
		virtual void SetZNear(const Math::realf&) = 0;
		virtual const Math::realf& GetZNear() const = 0;
		virtual void SetZFar(const Math::realf&) = 0;
		virtual const Math::realf& GetZFar() const = 0;
	};

		

	using IPerspectivePtr = Core::Pointer < IPerspective > ;

	inline IPerspectivePtr NewPerspective() {
		return System::CreateInstancePtr<IPerspective>(CLSID_Perspective, IID_IPerspective);
	}
}
PUNK_ENGINE_END

#endif	//	_H_IPERSPECTIVE
