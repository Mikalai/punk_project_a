#ifndef X11_WINDOW_H
#define X11_WINDOW_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "window.h"

namespace System
{
    class PUNK_ENGINE_API WindowX11 : public Window
    {
    public:
        WindowX11(const WindowDesc& desc = WindowDesc());
        ~WindowX11();

        ActionSlot<const WindowResizeEvent&> OnResizeEvent;
        ActionSlot<const KeyEvent&> OnKeyEvent;
        ActionSlot<const MouseEvent&> OnMouseEvent;
        ActionSlot<const MouseHooverEvent&> OnMouseHooverEvent;
        ActionSlot<const MouseWheelEvent&> OnMouseWheelEvent;

        int GetDesktopWidth() const override;
        int GetDesktopHeight() const override;
        int GetDesktopBitsPerPixel() const override;
        int GetDesktopRefreshRate() const override;
        int GetWidth() const override;
        int GetHeight() const override;
        int GetX() const override;
        int GetY() const override;
        void SetSize(int width, int height) override;
        void SetPosition(int x, int y) override;
        int Loop() override;
        void BreakMainLoop() override;
        void SetTitle(const string& text) override;
        const string GetTitle() const override;
        void Quite() override;
        void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;
        void DrawLine(int x1, int y1, int x2, int y2) override;
        void ShowCursor(bool value) override;

        Display* GetDisplay();
        void SetDisplay(Display* display);
        ::Window GetWindow();
        void SetWindow(::Window value);

    private:
        ::Window m_window;
        // Screen* m_screen;
        Colormap m_color_map;
        Display* m_display;
        XSetWindowAttributes m_swa;
        Atom wmDeleteWindow;
        int x_prev {0};
        int y_prev {0};
        int x {0};
        int y {0};
        bool m_exit_main_loop {false};
        bool m_left_button {false};
        bool m_right_button {false};
        bool m_middle_button {false};
    };
}

#endif // X11_WINDOW_H
