#ifndef _H_PROPERTY_WINDOW
#define _H_PROPERTY_WINDOW

#include <config.h>
#include "iwidget.h"

PUNK_ENGINE_BEGIN
namespace Gui {

	DECLARE_PUNK_GUID(IID_IPropertyWindow, "D3FC2AA8-5BBE-4BA5-A8DC-7BAA08A2C907");

	class IPropertyWindow : public Gui::IWidget {
	public:
		virtual void SetObject(Core::Pointer<Core::IObject> value) = 0;
		virtual void AddProperty(const Core::Guid& value) = 0;
		virtual void RemoveProperty(const Core::Guid& value) = 0;
	};

	extern "C" PUNK_ENGINE_API IPropertyWindow* CreatePropertyWindow();
}
PUNK_ENGINE_END

#endif	//	_H_PROPERTY_WINDOW