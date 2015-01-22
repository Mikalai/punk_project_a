#ifndef _H_IOPTICS
#define _H_IOPTICS

#include <config.h>
#include <core/iobject.h>
#include <system/factory/interface.h>
#include "iprojection.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IOptics, "615430E7-4720-4406-B132-03153351BC09");
	DECLARE_PUNK_GUID(CLSID_Optics, "2D67EE81-2FC7-4E6B-8DE0-8BD3DBABCFCC");

	class IOptics : public Core::IObject {
	public:
		virtual void SetProjection(IProjectionPtr value) = 0;
		virtual IProjectionPtr GetProjection() const = 0;
	};

	using IOpticsPtr = Core::Pointer < IOptics > ;

	inline IOpticsPtr NewOptics() {
		return System::CreateInstancePtr<IOptics>(CLSID_Optics, IID_IOptics);
	}
}
PUNK_ENGINE_END

#endif	//	_H_IOPTICS