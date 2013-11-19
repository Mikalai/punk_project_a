#ifdef _WIN32
#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include "window.h"
namespace System
{
    class PUNK_ENGINE_API WindowWin
    {
    public:
        Window(const WindowDesc& desc = WindowDesc());
        ~Window();

        ActionSlot<const WindowResizeEvent&> OnResizeEvent;
        ActionSlot<const KeyEvent&> OnKeyEvent;
        ActionSlot<const MouseEvent&> OnMouseEvent;
        ActionSlot<const MouseHooverEvent&> OnMouseHooverEvent;
        ActionSlot<const MouseWheelEvent&> OnMouseWheelEvent;

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
        void SetTitle(const string& text);
        const string GetTitle() const;
        void Quite();
        void DrawPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        void DrawLine(int x1, int y1, int x2, int y2);
        void ShowCursor(bool value);
#ifdef _WIN32
        LRESULT CustomDefWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        operator HWND ();
#elif defined __gnu_linux__
        Display* GetDisplay();
        void SetDisplay(Display* display);
        ::Window GetWindow();
        void SetWindow(::Window value);
#endif
        struct Impl;
        Impl* impl;
    };
}

#endif // WIN32_WINDOW_H
#endif //_win32
