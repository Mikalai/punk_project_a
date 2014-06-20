#ifdef __gnu_linux__
#ifndef X11_WINDOW_H
#define X11_WINDOW_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <system/input/module.h>
#include <system/time/module.h>

#include "window.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_API WindowX11 : public Window
    {
    public:
        WindowX11();
        virtual ~WindowX11();        

        void Initialize(const WindowDescription& desc) override;
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
        int Update(int dt) override;
        int Loop() override;
        void BreakMainLoop() override;
        void SetTitle(const Core::String& text) override;
        const Core::String GetTitle() const override;
        void Quite() override;
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


    protected:

        void InternalCreate() override;
        void InternalDestroy() override;

    private:
        WindowDescription m_window_description;
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
        ITimerUniquePtr m_timer{nullptr, Core::DestroyObject};

        IKeyBoard* m_keyboard {nullptr};
        IMouse* m_mouse {nullptr};        
    };
}
PUNK_ENGINE_END

#endif // X11_WINDOW_H
#endif  //__gnu_linux__
