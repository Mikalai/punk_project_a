#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

#include <memory>
#include <core/action.h>
#include <core/iobject.h>
#include <system/events/interface.h>
#include "window_description.h"

PUNK_ENGINE_BEGIN
namespace System {

    using ResizeEventDelegate = Core::ActionBasePtr<const WindowResizeEvent&>;
    using KeyEventDelegate = Core::ActionBasePtr<const KeyEvent&>;
    using CharEventDelegate = Core::ActionBasePtr<const KeyEvent&>;
    using MouseEventDelegate = Core::ActionBasePtr<const MouseEvent&>;
    using MouseMoveEventDelegate = Core::ActionBasePtr<const MouseEvent&>;
    using MouseHooverEventDelegate = Core::ActionBasePtr<const MouseHooverEvent&>;
    using MouseWheelEventDelegate = Core::ActionBasePtr<const MouseWheelEvent&>;
    using WindowCreatedDelegate = Core::ActionBasePtr<void>;
    using WindowDestroyDelegate = Core::ActionBasePtr<void>;
    using IdleEventDelegate = Core::ActionBasePtr<const IdleEvent&>;

	static const Core::Guid IID_IWindow{ "2CDB7400-50E8-4C02-B75D-DA9AA7524390" };

    class IWindow : public virtual Core::IObject {
    public:
		virtual void Initialize(const WindowDescription& desc) = 0;
        virtual int GetDesktopWidth() const = 0;
        virtual int GetDesktopHeight() const = 0;
        virtual int GetDesktopBitsPerPixel() const = 0;
        virtual int GetDesktopRefreshRate() const = 0;
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
        virtual int GetX() const = 0;
        virtual int GetY() const = 0;
        virtual void SetSize(int width, int height) = 0;
        virtual void SetPosition(int x, int y) = 0;
		virtual int Update(int dt) = 0;
        virtual int Loop() = 0;
        virtual void BreakMainLoop() = 0;
        virtual void SetTitle(const Core::String& text) = 0;
        virtual const Core::String GetTitle() const = 0;
        virtual void Quite() = 0;
        virtual void ShowCursor(bool value) = 0;
        virtual void SubscribeResizeEvent(ResizeEventDelegate) = 0;
        virtual void UnsubscribeResizeEvent(ResizeEventDelegate) = 0;
        virtual void SubscribeKeyEvent(KeyEventDelegate) = 0;
        virtual void UnsubscribeKeyEvent(KeyEventDelegate) = 0;
        virtual void SubscribeCharEvent(CharEventDelegate) = 0;
        virtual void UnsubscribeCharEvent(CharEventDelegate) = 0;
        virtual void SubscribeMouseEvent(MouseEventDelegate) = 0;
        virtual void UnsubscribeMouseEvent(MouseEventDelegate) = 0;
        virtual void SubscribeMouseEvent(void (*Delegate)(const MouseEvent&)) = 0;
        virtual void UnsubscribeMouseEvent(void (*Delegate)(const MouseEvent&)) = 0;
        virtual void SubscribeMouseMoveEvent(MouseMoveEventDelegate) = 0;
        virtual void UnsubscribeMouseMoveEvent(MouseMoveEventDelegate) = 0;
        virtual void SubscribeMouseHooverEvent(MouseHooverEventDelegate) = 0;
        virtual void UnsubscribeMouseHooverEvent(MouseHooverEventDelegate) = 0;
        virtual void SubscribeMouseWheelEvent(MouseWheelEventDelegate) = 0;
        virtual void UnsubscribeMouseWheelEvent(MouseWheelEventDelegate) = 0;
        virtual void SubscribeWindowCreatedEvent(WindowCreatedDelegate) = 0;
        virtual void UnsubscribeWindowCreatedEvent(WindowCreatedDelegate) = 0;
        virtual void SubscribeWindowDestroyEvent(WindowDestroyDelegate) = 0;
        virtual void SubscribeWindowDestroyEvent(void (*Delegate)()) = 0;
        virtual void UnsubscribeWindowDestroyEvent(WindowDestroyDelegate) = 0;
        virtual void UnsubscribeWindowDestroyEvent(void (*Delegate)()) = 0;
        virtual void SubscribeIdleEvent(IdleEventDelegate) = 0;        
        virtual void UnsubscribeIdleEvent(IdleEventDelegate) = 0;
        virtual void SubscribeIdleEvent(void (*Delegate)(const IdleEvent&)) = 0;
        virtual void UnsubscribeIdleEvent(void (*Delegate)(const IdleEvent&)) = 0;
        virtual void Open() = 0;
        virtual void Close() = 0;
		virtual void InternalCreate() = 0;
		virtual void InternalDestroy() = 0;

#ifdef _WIN32
		virtual HWND GetNativeHandle() = 0;
#endif	//	 _WIN32			
    };
	
	using IWindowUniquePtr = std::unique_ptr < IWindow, void(*)(Core::IObject*) > ;	
}
PUNK_ENGINE_END

#endif // WINDOW_INTERFACE_H
