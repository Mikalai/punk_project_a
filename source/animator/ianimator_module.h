#ifndef _H_IANIMTOR_MODULE
#define _H_IANIMTOR_MODULE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace AnimatorModule {

	DECLARE_PUNK_GUID(IID_IAnimatorModule, "B2111F88-D2A3-47E3-9D8E-DC98B324BBE8");

	class IAnimatorModule : public Core::IObject {
	public:
	};
}
PUNK_ENGINE_END

#endif	//	_H_IANIMTOR_MODULE
