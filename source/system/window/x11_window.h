#ifdef __gnu_linux__
#ifndef X11_WINDOW_H
#define X11_WINDOW_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "system/input/module.h"

#include "window.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API WindowX11 : public Window
    {
    public:
        WindowX11(const WindowDesc& desc = WindowDesc());
        virtual ~WindowX11();        

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
        void SetTitle(const Core::String& text) override;
        const Core::String GetTitle() const override;
        void Quite() override;
        void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;
        void DrawLine(int x1, int y1, int x2, int y2) override;
        void ShowCursor(bool value) override;

        Display* GetDisplay();
        void SetDisplay(Display* display);
        ::Window GetWindow();
        void SetWindow(::Window value);
        int DecodeKey(KeySym keysym, int& charKey, bool press);
        void OnKeyPressRelease(XKeyEvent* event);
        void OnMousePressRelease(XEvent* event);
        bool IsClosed();

        void MouseMoveProc(const MouseEvent& e);

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

        IKeyBoard* m_keyboard {nullptr};
        IMouse* m_mouse {nullptr};

        PUNK_OBJECT(WindowX11)
    };
}
PUNK_ENGINE_END

#endif // X11_WINDOW_H
#endif  //__gnu_linux__
