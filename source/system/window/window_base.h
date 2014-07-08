#ifndef _H_PUNK_SYSTEM_WINDOW
#define _H_PUNK_SYSTEM_WINDOW

#include <map>

#include "config.h"
#include <string/string.h>
#include "core/action.h"
#include <core/container.h>
#include "system/events/interface.h"
#include "window_description.h"
#include "iwindow.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_LOCAL WindowBase : public IWindow
	{	
    public:
        WindowBase();

        virtual ~WindowBase();

/*        virtual int GetDesktopWidth() const override;
        virtual int GetDesktopHeight() const override;
        virtual int GetDesktopBitsPerPixel() const override;
        virtual int GetDesktopRefreshRate() const override;
        virtual int GetWidth() const override;
        virtual int GetHeight() const override;
        virtual int GetX() const override;
        virtual int GetY() const override;
        virtual void SetSize(int width, int height) override;
        virtual void SetPosition(int x, int y) override;
		virtual int Update(int dt) override;
        virtual int Loop() override;
        virtual void BreakMainLoop() override;
        virtual void SetTitle(const Core::String& text) override;
        virtual const Core::String GetTitle() const override;
        virtual void Quite() override;
        virtual void ShowCursor(bool value) override; */       

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
	};    
}
PUNK_ENGINE_END

#endif	//_H_PUNK_SYSTEM_WINDOW
