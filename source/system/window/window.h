#ifndef _H_PUNK_SYSTEM_WINDOW
#define _H_PUNK_SYSTEM_WINDOW

#include <map>

#include "config.h"
#include "string/string.h"
#include "core/action.h"
#include "core/object.h"
#include "system/events/interface.h"
#include "window_description.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API Window : public Core::Object
	{	
    public:
        Window();
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

        PUNK_OBJECT(Window)
	};

    PUNK_ENGINE_API Window* CreateRootWindow(const WindowDesc& desc);
}
PUNK_ENGINE_END

#endif	//_H_PUNK_SYSTEM_WINDOW
