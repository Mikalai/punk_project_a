#ifndef _H_ICOLLECTION_TAB
#define _H_ICOLLECTION_TAB

#include <config.h>
#include "itab.h"
#include <attributes/collection/icollection.h>
#include <core/pointer.h>

PUNK_ENGINE_BEGIN
namespace Gui {

	DECLARE_PUNK_GUID(IID_ICollectionTab, "78676F85-BE61-4014-B915-5A9647D72BB5");

	class ICollectionTab : public ITab {
	public:
		virtual void SetObject(Core::Pointer<Attributes::ICollection> value) = 0;
	};

	extern "C" PUNK_ENGINE_API Gui::ICollectionTab* CreateCollectionTab();
}
PUNK_ENGINE_END

#endif	//	_H_ICOLLECTION_TAB