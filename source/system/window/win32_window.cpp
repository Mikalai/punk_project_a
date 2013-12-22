#ifdef _WIN32

#include <stdio.h>
#include <algorithm>
#include "win32_window.h"
#include "error/module.h"
#include "system/events/module.h"
#include "system/errors/module.h"
#include "system/logger/module.h"
#include "system/input/module.h"
#include "system/time/module.h"
#include "string/module.h"

PUNK_ENGINE_BEGIN
namespace System {

    LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    typedef LRESULT WINAPI (*TWindowCallBack)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    int GetX(HWND handle) {
        RECT wrect;
        GetClientRect(handle, &wrect);
        return wrect.left;
    }

    int GetY(HWND handle) {
        RECT wrect;
        GetClientRect(handle, &wrect);
        return wrect.top;
    }

    int GetWidth(HWND handle) {
        RECT rect;
        GetClientRect(handle, &rect);
        return rect.right - rect.left;
    }

    int GetHeight(HWND handle) {
        RECT rect;;
        GetClientRect(handle, &rect);
        return rect.bottom - rect.top;
    }

    WindowWin::WindowWin(const WindowDesc& desc) {
        if (desc.parent_wnd) {
            m_use_parent_window = true;
            m_hwindow = desc.parent_wnd;
        }
        else {
            m_use_parent_window = false;
            WNDCLASS wc;
            wc.cbClsExtra = 0;
            wc.cbWndExtra = 0;
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wc.hCursor = LoadCursor(0, IDC_ARROW);
            wc.hIcon = LoadIcon(0, IDI_APPLICATION);
            wc.hInstance = GetModuleHandle(0);
            wc.lpfnWndProc = WindowCallBack;
            wc.lpszClassName = TEXT("Punk Render");
            wc.lpszMenuName = 0;
            wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

            if (!RegisterClass(&wc))
                throw Error::PunkInvalidArgumentException(L"Can't register window class");

            RECT rect;
            rect.left = desc.m_x;
            rect.right = desc.m_x + desc.m_width;
            rect.top = desc.m_y;
            rect.bottom = desc.m_y + desc.m_height;


            DWORD style = WS_OVERLAPPEDWINDOW;
            DWORD styleEx = 0;

            AdjustWindowRectEx(&rect, style, false, styleEx);

            m_hwindow = CreateWindowEx(styleEx, TEXT("Punk Render"), TEXT("Punk Engine"), style,
                                       0, 0, rect.right-rect.left, rect.bottom-rect.top, 0, 0,
                                       GetModuleHandle(0), (void*)this);

            SetWindowLongPtr(m_hwindow, GWLP_USERDATA, (LONG)this);

            if (!m_hwindow)
                throw Error::PunkInvalidArgumentException(L"Can't create window");

            GetClientRect(m_hwindow, &rect);
            ShowWindow(m_hwindow, SW_SHOW);
            UpdateWindow(m_hwindow);
        }
    }

    WindowWin::~WindowWin()
    {
        //SetWindowLongW(m_hwindow, GWL_WNDPROC, (LONG)m_prev_hwnd_func);
        DestroyWindow(m_hwindow);
    }

    int WindowWin::GetDesktopWidth() const
    {
        DEVMODE mode;
        memset(&mode, 0, sizeof(mode));
        mode.dmSize = sizeof(mode);

        if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
            return 480;
        return mode.dmPelsWidth;
    }

    int WindowWin::GetDesktopHeight() const
    {
        DEVMODE mode;
        memset(&mode, 0, sizeof(mode));
        mode.dmSize = sizeof(mode);

        if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
            return 640;
        return mode.dmPelsHeight;
    }

    int WindowWin::GetDesktopBitsPerPixel() const
    {
        DEVMODE mode;
        memset(&mode, 0, sizeof(mode));
        mode.dmSize = sizeof(mode);

        if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
            return 16;
        return mode.dmBitsPerPel;
    }

    int WindowWin::GetDesktopRefreshRate() const
    {
        DEVMODE mode;
        memset(&mode, 0, sizeof(mode));
        mode.dmSize = sizeof(mode);

        if (!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode))
            return 60;
        return mode.dmDisplayFrequency;
    }

    int WindowWin::GetWidth() const
    {
        RECT rect;
        GetClientRect(m_hwindow, &rect);
        return rect.right - rect.left;
    }

    int WindowWin::GetHeight() const
    {
        RECT rect;;
        if (!GetClientRect(m_hwindow, &rect))
            throw Error::PunkInvalidArgumentException(L"Can't get window height");
        //GetWindowRect(m_hwindow, &rect);
        return rect.bottom - rect.top;
    }

    int WindowWin::GetX() const
    {
        RECT wrect;
        GetClientRect(m_hwindow, &wrect);
        return wrect.left;
    }

    int WindowWin::GetY() const
    {
        RECT wrect;
        GetClientRect(m_hwindow, &wrect);
        return wrect.top;
    }

    void WindowWin::SetSize(int width, int height)
    {
        RECT r;
        GetWindowRect(m_hwindow, &r);
        r.right = r.left + width;
        r.bottom = r.top + height;
        AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
        MoveWindow(m_hwindow, r.left, r.top, width, height, TRUE);
    }

    void WindowWin::SetPosition(int x, int y)
    {
        RECT r;
        GetWindowRect(m_hwindow, &r);
        MoveWindow(m_hwindow, x, y, r.right - r.left, r.bottom - r.top, TRUE);
    }



    int WindowWin::Loop()
    {
        ITimer* timer = CreateTimer();
        timer->Reset();

        if (m_use_parent_window)
            return 0;

        MSG msg;
        while (1)
        {
            while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
            {
                if (GetMessage(&msg, 0, 0, 0))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                {
                    return 0;
                }
            }

            IdleEvent e;
            e.elapsed_time_s = timer->GetElapsedSeconds();
            timer->Reset();
            OnIdleEvent(e);
        }
        return 0;
    }

    void WindowWin::BreakMainLoop()
    {
        PostQuitMessage(0);
    }

    void WindowWin::SetTitle(const Core::String& text)
    {
        SetWindowTextW(m_hwindow, (LPWSTR)text.ToWchar().Data());
    }

    const Core::String WindowWin::GetTitle() const
    {
        wchar_t buf[256];
        GetWindowTextW(m_hwindow, buf, 256);
        return Core::String(buf);
    }

    void WindowWin::Quite()
    {
        SendMessageW(m_hwindow, WM_DESTROY, 0, 0);
    }

    WindowWin::operator HWND ()
    {
        return m_hwindow;
    }

    LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        WindowWin* win = reinterpret_cast<WindowWin*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

        static int x_prev = 0;
        static int y_prev = 0;
        static int x = 0;
        static int y = 0;

        switch (msg)
        {
        case WM_MBUTTONUP:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        {
            MouseEvent event;
            event.leftButton = (msg == WM_LBUTTONUP);
            event.middleButton = (msg == WM_MBUTTONUP);
            event.rightButton = (msg == WM_RBUTTONUP);
            event.x = LOWORD(lParam);
            event.y = GetHeight(hwnd) - HIWORD(lParam);
            event.x_prev = x_prev;
            event.y_prev = y_prev;

            x_prev = event.x;
            y_prev = event.y;
            event.controlKey = (wParam & MK_CONTROL) != 0;
            event.leftButton = (wParam & MK_LBUTTON) != 0;
            event.middleButton = (wParam & MK_MBUTTON) != 0;
            event.rightButton = (wParam & MK_RBUTTON) != 0;
            event.shiftButton = (wParam & MK_SHIFT) != 0;
            event.xbutton1 = (wParam & MK_XBUTTON1) != 0;
            event.xbutton2 = (wParam & MK_XBUTTON2) != 0;
            if (msg == WM_LBUTTONUP)
                GetMouse()->SetButtonState(MouseButtons::LeftButton, false);
            if (msg == WM_MBUTTONUP)
                GetMouse()->SetButtonState(MouseButtons::MiddleButton, false);
            if (msg == WM_RBUTTONUP)
                GetMouse()->SetButtonState(MouseButtons::RightButton, false);
            win->OnMouseEvent(event);
        }
            break;
        case WM_MBUTTONDOWN:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        {
            MouseEvent event;
            event.x = LOWORD(lParam);
            event.y = GetHeight(hwnd) - HIWORD(lParam);
            event.x_prev = x_prev;
            event.y_prev = y_prev;
            x_prev = event.x;
            y_prev = event.y;
            event.leftButton = (msg == WM_LBUTTONDOWN);
            event.middleButton = (msg == WM_MBUTTONDOWN);
            event.rightButton = (msg == WM_RBUTTONDOWN);
            event.controlKey = (wParam & MK_CONTROL) != 0;
            event.leftButton = (wParam & MK_LBUTTON) != 0;
            event.middleButton = (wParam & MK_MBUTTON) != 0;
            event.rightButton = (wParam & MK_RBUTTON) != 0;
            event.shiftButton = (wParam & MK_SHIFT) != 0;
            event.xbutton1 = (wParam & MK_XBUTTON1) != 0;
            event.xbutton2 = (wParam & MK_XBUTTON2) != 0;
            if (msg == WM_LBUTTONDOWN)
                GetMouse()->SetButtonState(MouseButtons::LeftButton, true);
            if (msg == WM_MBUTTONDOWN)
                GetMouse()->SetButtonState(MouseButtons::MiddleButton, true);
            if (msg == WM_RBUTTONDOWN)
                GetMouse()->SetButtonState(MouseButtons::RightButton, true);
            win->OnMouseEvent(event);
        }
            break;
        case WM_MOUSEHOVER:
        {
            MouseHooverEvent event;
            event.x = LOWORD(lParam);
            event.y = GetHeight(hwnd) - HIWORD(lParam);
            event.x_prev = x_prev;
            event.y_prev = y_prev;
            win->OnMouseHooverEvent(event);
        }
            break;
        case WM_MOUSEMOVE:
        {
            MouseEvent event;
            x_prev = x;
            y_prev = y;
            event.x = LOWORD(lParam);
            event.y = HIWORD(lParam);

            event.x = x;
            event.y = GetHeight(hwnd) - y;
            event.x_prev = x_prev;
            event.y_prev = GetHeight(hwnd) - y_prev;
            event.controlKey = (wParam & MK_CONTROL) != 0;
            event.leftButton = (wParam & MK_LBUTTON) != 0;
            event.middleButton = (wParam & MK_MBUTTON) != 0;
            event.rightButton = (wParam & MK_RBUTTON) != 0;
            event.shiftButton = (wParam & MK_SHIFT) != 0;
            event.xbutton1 = (wParam & MK_XBUTTON1) != 0;
            event.xbutton2 = (wParam & MK_XBUTTON2) != 0;

            if (GetMouse()->IsLocked())
            {
                RECT r, r2;
                GetWindowRect(hwnd, &r);
                GetClientRect(hwnd, &r2);
                int c_x = (r.left + r.right) / 2;
                int c_y = (r.top + r.bottom) / 2;
                POINT p = {c_x, c_y};
                ClientToScreen(hwnd, &p);
                if (x != x_prev || y != y_prev)
                {
                    x = x_prev = c_x;
                    y = y_prev = c_y;
                    SetCursorPos(p.x, p.y);
                }
            }

            TRACKMOUSEEVENT te;
            memset(&te, 0, sizeof(te));
            te.cbSize = sizeof(te);
            te.dwFlags = TME_HOVER;
            te.dwHoverTime = 400;
            te.hwndTrack = hwnd;
            TrackMouseEvent(&te);
            win->OnMouseMoveEvent(event);
        }
            break;
        case WM_MOUSEWHEEL:
        {
            POINT p = {LOWORD(lParam), HIWORD(lParam)};
            ScreenToClient(hwnd, &p);
            MouseWheelEvent event;
            event.x = p.x;
            event.y = GetHeight(hwnd) - p.y;
            event.x_prev = x_prev;
            event.y_prev = y_prev;
            x_prev = event.x;
            y_prev = event.y;
            event.delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            event.controlKey = (wParam & MK_CONTROL) != 0;
            event.leftButton = (wParam & MK_LBUTTON) != 0;
            event.middleButton = (wParam & MK_MBUTTON) != 0;
            event.rightButton = (wParam & MK_RBUTTON) != 0;
            event.shiftButton = (wParam & MK_SHIFT) != 0;
            event.xbutton1 = (wParam & MK_XBUTTON1) != 0;
            event.xbutton2 = (wParam & MK_XBUTTON2) != 0;
            win->OnMouseWheelEvent(event);
        }
            break;
        case WM_CHAR:
        {
            KeyEvent event;
            event.key = (int)wParam;
            event.repeat_count = (lParam & 0xFFFF) != 0;
            event.scan_code = (lParam & 0xFF0000) != 0;
            event.isExtended = (lParam & 0x1000000) != 0;
            event.isAltPressed = (lParam & 0x20000000) != 0;
            event.prevState = (lParam & 0x40000000) != 0;
            event.transitionState = (lParam & 0x80000000) != 0;
            win->OnCharEvent(event);
        }
            break;
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYUP:
        {
            KeyEvent event;
            event.key = (int)wParam;
            event.repeat_count = (lParam & 0xFFFF) != 0;
            event.scan_code = (lParam & 0xFF0000) != 0;
            event.isExtended = (lParam & 0x1000000) != 0;
            event.prevState = (lParam & 0x40000000) != 0;
            event.transitionState = (lParam & 0x80000000) != 0;
            GetKeyboard()->SetKeyState(wParam, true);
            win->OnKeyEvent(event);
            break;
        }
        case WM_SIZE:
        {
            WindowResizeEvent event;
            event.minimized = (wParam & SIZE_MINIMIZED) != 0;
            event.restored = (wParam & SIZE_RESTORED) != 0;
            event.width = LOWORD(lParam);
            event.height = HIWORD(lParam);
            win->OnResizeEvent(event);
        }
            break;
        case WM_CREATE:
        {
            CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
            RECT r;
            GetWindowRect(hwnd, &r);
            x_prev = (r.left + r.right)/2;
            y_prev = (r.top + r.bottom)/2;
            SetCursorPos((r.left+r.right)/2, (r.top+r.bottom)/2);
            WindowWin* a = reinterpret_cast<WindowWin*>(cs->lpCreateParams);
            a->OnWindowCreated();
        }
            break;
        case WM_DESTROY:
            win->OnWindowDestroy();
            PostQuitMessage(0);
            break;
        }
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    void WindowWin::ShowCursor(bool value) {
        ::ShowCursor(value);
    }
}
PUNK_ENGINE_END

#endif	//	_WIN32
