#ifndef _H_PUNK_QT_INTERFACE
#define _H_PUNK_QT_INTERFACE

#include <functional>
#include <config.h>
#include "iobject_tab.h"
#include "itab_holder.h"

PUNK_ENGINE_BEGIN
namespace Qt {
	extern "C" PUNK_ENGINE_API Gui::IObjectTab* CreateIObjectTab();
	extern "C" PUNK_ENGINE_API Gui::ITabHolder* CreateTabHolder();
	extern "C" PUNK_ENGINE_API void RunGuiThread(Core::Pointer<Gui::IWidget> (*func)());
}
PUNK_ENGINE_END


#endif	//	_H_PUNK_QT_INTERFACE