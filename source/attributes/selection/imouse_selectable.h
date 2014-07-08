#ifndef _H_IMOUSE_SELECTABLE
#define _H_IMOUSE_SELECTABLE

#include <config.h>
#include <core/action.h>
#include <system/input/imouse.h>
#include "iselectable.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IMouseSelectable, "F674F8A3-F677-4F74-8571-13A8DC3F91F4");

	using MouseMovedAction = Core::Pointer < Core::ActionBase < float, float> > ;
	using MousePressedAction = Core::Pointer < Core::ActionBase < float, float, System::MouseButtons > >;
	using MouseReleasedAction = Core::Pointer < Core::ActionBase < float, float, System::MouseButtons > >;
	using MouseEnteredAction = Core::Pointer < Core::ActionBase < float, float > > ;
	using MouseLeavedAction = Core::Pointer < Core::ActionBase < float, float> >;
	using MouseEnterNotifyAction = Core::Pointer < Core::ActionBase < void > >;
	using MouseLeaveNotifyAction = Core::Pointer < Core::ActionBase < void > >;
	using MouseClickedAction = Core::Pointer < Core::ActionBase < float, float, System::MouseButtons > >;
	using FocusedAction = Core::Pointer < Core::ActionBase < bool > >;

	class IMouseSelectable : public ISelectable {
	public:
		virtual void SubscribeOnMouseMoved(MouseMovedAction value) = 0;
		virtual void SubscribeOnMousePressed(MousePressedAction value) = 0;
		virtual void SubscribeOnMouseReleased(MouseReleasedAction value) = 0;
		virtual void SubscribeOnMouseEntered(MouseEnteredAction value) = 0;
		virtual void SubscribeOnMouseLeaved(MouseLeavedAction value) = 0;
		virtual void SubscribeOnMouseEnterNotify(MouseEnterNotifyAction value) = 0;
		virtual void SubscribeOnMouseLeaveNotify(MouseLeaveNotifyAction value) = 0;		
		virtual void SubscribeOnMouseClicked(MouseClickedAction value) = 0;
		virtual void SubscribeOnFocusedAction(FocusedAction value) = 0;
		virtual void EmitMouseMoveEvent(float x, float y) = 0; 
		virtual void EmitMousePressEvent(float x, float y, System::MouseButtons button) = 0;
		virtual void EmitMouseReleaseEvent(float x, float y, System::MouseButtons button) = 0;
		virtual void EmitMouseEnterEvent(float x, float y) = 0;
		virtual void EmitMouseLeaveEvent(float x, float y) = 0;
		virtual void EmitMouseClickEvent(float x, float y, System::MouseButtons button) = 0;
		virtual void EmitFocusEvent() = 0;
		virtual void EmitUnfocusEvent() = 0;

	};
}
PUNK_ENGINE_END

#endif	//	_H_IMOUSE_SELECTABLE