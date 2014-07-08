#ifndef _H_ISELECTABLE
#define _H_ISELECTABLE

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Math {
	class IBoundingVolume;
}
namespace Attributes {

	DECLARE_PUNK_GUID(IID_ISelectable, "A28B4214-9A25-458A-847D-3E3E4770D952");

	class ISelectable : public Core::IObject {
	public:
		virtual void EnableSelection(bool value) = 0;
		virtual bool IsSelectionEnabled() const = 0;
		virtual void Select(bool flag) = 0;
		virtual bool IsSelected() const = 0;		
		virtual void ToggleSelection() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ISELECTABLE