#ifdef _WIN32
#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include "window.h"
#include "core/action.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace System
{
    class PUNK_ENGINE_API WindowWin : public Window
    {
    public:
        WindowWin(const WindowDesc& desc = WindowDesc());
        ~WindowWin();

        Core::ActionSlot<const WindowResizeEvent&> OnResizeEvent;
        Core::ActionSlot<const KeyEvent&> OnKeyEvent;
        Core::ActionSlot<const MouseEvent&> OnMouseEvent;
        Core::ActionSlot<const MouseHooverEvent&> OnMouseHooverEvent;
        Core::ActionSlot<const MouseWheelEvent&> OnMouseWheelEvent;

        int GetDesktopWidth() const;
        int GetDesktopHeight() const;
        int GetDesktopBitsPerPixel() const;
        int GetDesktopRefreshRate() const;
        int GetWidth() const;
        int GetHeight() const;
        int GetX() const;
        int GetY() const;
        void SetSize(int width, int height);
        void SetPosition(int x, int y);
        int Loop();
        void BreakMainLoop();
        void SetTitle(const Core::String& text);
        const Core::String GetTitle() const;
        void Quite();
        void ShowCursor(bool value);
        operator HWND ();

    private:
        HWND m_hwindow;
        bool m_use_parent_window;

    };
}
PUNK_ENGINE_END

#endif // WIN32_WINDOW_H
#endif //_win32
