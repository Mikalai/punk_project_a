#ifndef _H_ITAB_HOLDER
#define _H_ITAB_HOLDER

#include <config.h>
#include "iwidget.h"

PUNK_ENGINE_BEGIN
namespace Gui {

	class ITab;

	DECLARE_PUNK_GUID(IID_ITabHolder, "4ECD54EF-EA1E-4F87-9720-790362419DDB");

	class ITabHolder : public IWidget {
	public:
		virtual void AddTab(const Core::String& name, Core::Pointer<ITab> value) = 0;
		virtual void RemoveTab(const Core::String& name) = 0;
		virtual void RemoveTab(Core::Pointer<ITab> value) = 0;
	};

	extern "C" PUNK_ENGINE_API Gui::ITabHolder* CreateTabHolder();
}
PUNK_ENGINE_END

#endif	//	_H_ITAB_HOLDER