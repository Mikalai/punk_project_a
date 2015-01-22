#ifndef _H_IPROJECTION
#define _H_IPROJECTION

#include <config.h>
#include <system/factory/interface.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IProjection, "69EF1F1D-778E-482A-881D-3770FB2EC35E");

	class IProjection : public Core::IObject {
	public:
	};

	using IProjectionPtr = Core::Pointer < IProjection >;
}
PUNK_ENGINE_END

#endif	//	_H_IPROJECTION
