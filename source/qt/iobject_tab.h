#ifndef _H_IOBJECT_TAB
#define _H_IOBJECT_TAB

#include <config.h>
#include "itab.h"
#include <core/iobject.h>
#include <core/pointer.h>

PUNK_ENGINE_BEGIN
namespace Gui {

	DECLARE_PUNK_GUID(IID_IObjectTab, "5D4E4985-55ED-4B0F-8D2F-2D2996F3F8F0");

	class IObjectTab : public ITab {
	public:
		virtual void SetObject(Core::Pointer<Core::IObject> value) = 0;
	};

	extern "C" PUNK_ENGINE_API Gui::IObjectTab* CreateIObjectTab();

}
PUNK_ENGINE_END

#endif	//	_H_IOBJECT_TAB