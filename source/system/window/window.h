#ifndef _H_PUNK_SYSTEM_WINDOW
#define _H_PUNK_SYSTEM_WINDOW

#include <map>

#include "config.h"
#include "string/string.h"
#include "core/action.h"
#include "core/object.h"
#include "system/events/interface.h"
#include "window_description.h"
#include "window_interface.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API Window : public IWindow, public Core::Object
	{	
    public:
        Window();        

        virtual ~Window();
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
        virtual int Loop() = 0;
        virtual void BreakMainLoop() = 0;
        virtual void SetTitle(const Core::String& text) = 0;
        virtual const Core::String GetTitle() const = 0;
        virtual void Quite() = 0;
        virtual void ShowCursor(bool value) = 0;        

        virtual void SubscribeResizeEvent(ResizeEventDelegate) override;
        virtual void UnsubscribeResizeEvent(ResizeEventDelegate) override;
        virtual void SubscribeKeyEvent(KeyEventDelegate) override;
        virtual void UnsubscribeKeyEvent(KeyEventDelegate) override;
        virtual void SubscribeCharEvent(CharEventDelegate) override;
        virtual void UnsubscribeCharEvent(CharEventDelegate) override;
        virtual void SubscribeMouseEvent(MouseEventDelegate) override;
        virtual void UnsubscribeMouseEvent(MouseEventDelegate) override;
        virtual void SubscribeMouseEvent(void (*Delegate)(const MouseEvent&)) override;
        virtual void UnsubscribeMouseEvent(void (*Delegate)(const MouseEvent&)) override;
        virtual void SubscribeMouseMoveEvent(MouseMoveEventDelegate) override;
        virtual void UnsubscribeMouseMoveEvent(MouseMoveEventDelegate) override;
        virtual void SubscribeMouseHooverEvent(MouseHooverEventDelegate) override;
        virtual void UnsubscribeMouseHooverEvent(MouseHooverEventDelegate) override;
        virtual void SubscribeMouseWheelEvent(MouseWheelEventDelegate) override;
        virtual void UnsubscribeMouseWheelEvent(MouseWheelEventDelegate) override;
        virtual void SubscribeWindowCreatedEvent(WindowCreatedDelegate) override;
        virtual void UnsubscribeWindowCreatedEvent(WindowCreatedDelegate) override;
        virtual void SubscribeWindowDestroyEvent(WindowDestroyDelegate) override;
        virtual void SubscribeWindowDestroyEvent(void (*Delegate)()) override;
        virtual void UnsubscribeWindowDestroyEvent(WindowDestroyDelegate) override;
        virtual void UnsubscribeWindowDestroyEvent(void (*Delegate)()) override;
        virtual void SubscribeIdleEvent(IdleEventDelegate) override;
        virtual void UnsubscribeIdleEvent(IdleEventDelegate) override;
        virtual void SubscribeIdleEvent(void (*Delegate)(const IdleEvent&)) override;
        virtual void UnsubscribeIdleEvent(void (*Delegate)(const IdleEvent&)) override;

        virtual void Open() override;
        virtual void Close() override;

    protected:

        virtual void InternalCreate() = 0;
        virtual void InternalDestroy() = 0;

    protected:

        Core::ActionSlot<const WindowResizeEvent&> OnResizeEvent;
        Core::ActionSlot<const KeyEvent&> OnKeyEvent;
        Core::ActionSlot<const KeyEvent&> OnCharEvent;
        Core::ActionSlot<const MouseEvent&> OnMouseEvent;
        Core::ActionSlot<const MouseEvent&> OnMouseMoveEvent;
        Core::ActionSlot<const MouseHooverEvent&> OnMouseHooverEvent;
        Core::ActionSlot<const MouseWheelEvent&> OnMouseWheelEvent;
        Core::ActionSlot<void> OnWindowCreated;
        Core::ActionSlot<void> OnWindowDestroy;
        Core::ActionSlot<const IdleEvent&> OnIdleEvent;
        bool m_initialized = false;

        PUNK_OBJECT(Window)                               
	};

    PUNK_ENGINE_API Window* CreateRootWindow(const WindowDescription& desc);
}
PUNK_ENGINE_END

#endif	//_H_PUNK_SYSTEM_WINDOW
