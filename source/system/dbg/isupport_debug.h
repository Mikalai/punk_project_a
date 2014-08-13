#ifndef _H_ISUPPORT_DEBUG
#define _H_ISUPPORT_DEBUG

#include <config.h>
#include <string/string.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace System {

	DECLARE_PUNK_GUID(IID_ISupportDebugger, "749F63F4-74B2-4C3E-86A5-4BB61C487BA2");

	class ISupportDebug : public Core::IObject {
	public:
		virtual const Core::String GetCreationPlace() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ISUPPORT_DEBUG