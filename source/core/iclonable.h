#ifndef _H_ICLONABLE
#define _H_ICLONABLE

#include "iobject.h"

PUNK_ENGINE_BEGIN
namespace Core {

	DECLARE_PUNK_GUID(IID_IClonable, "16857BE0-4128-4169-8961-7ECA9D33F3B2");

	class IClonable : public Core::IObject {
	public:
		virtual Core::Pointer<IClonable> Clone() const = 0;
	};

}
PUNK_ENGINE_END

#endif	//	_H_ICLONABLE