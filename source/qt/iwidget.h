#ifndef H_IWIDGET
#define H_IWIDGET

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Gui {

	DECLARE_PUNK_GUID(IID_IWidget, "B1A7DF8B-353A-4DB0-8A1D-68E8AB3113E3");

	class IWidget : public Core::IObject {
	public:
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual bool IsVisible() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	H_IWIDGET