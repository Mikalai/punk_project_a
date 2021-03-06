#ifdef _WIN32

#include <typeinfo>
#include <stdio.h>
#include <algorithm>
#include <system/factory/module.h>
#include <system/events/module.h>
#include <system/errors/module.h>
#include <system/logger/module.h>
#include <system/input/module.h>
#include <system/time/module.h>
#include <string/module.h>
#include <system/time/module.h>
#include <core/action.h>
#include "window_base.h"

PUNK_ENGINE_BEGIN
namespace System {    
    
	LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	class PUNK_ENGINE_LOCAL WindowWin : public WindowBase
	{
	public:
		WindowWin();
		~WindowWin();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IWindow
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
		HWND GetNativeHandle() override;

	protected:

		void InternalCreate() override;
		void InternalDestroy() override;

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		HWND m_hwindow;
		bool m_use_parent_window;
		WindowDescription m_window_description;
		Core::Pointer<ITimer> m_timer{ nullptr, Core::DestroyObject };

		friend LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

    PUNK_REGISTER_CREATOR(IID_IWindow, (System::CreateInstance<WindowWin, IWindow>));

	void WindowWin::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IWindow });
	}

	std::uint32_t WindowWin::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t WindowWin::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

	typedef LRESULT (WINAPI *TWindowCallBack)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

    WindowWin::WindowWin()
    {
		m_timer = System::CreateInstancePtr<ITimer>(CLSID_Timer, IID_ITimer);		
	}

	void WindowWin::Initialize(const WindowDescription& desc) {
		m_window_description = desc;
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
            throw Error::InvalidArgumentException(L"Can't get window height");
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
		if (m_window_description.parent_wnd) {
			/*GetClientRect(m_window_description.parent_wnd, &r);
			width = r.right - r.left;
			height = r.bottom - r.top;*/
			MoveWindow(m_hwindow, 0, 0, width, height, TRUE);
		}
		else {
			GetWindowRect(m_hwindow, &r);
			r.right = r.left + width;
			r.bottom = r.top + height;
			AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
			MoveWindow(m_hwindow, r.left, r.top, width, height, TRUE);
		}
    }

    void WindowWin::SetPosition(int x, int y)
    {
        RECT r;
        GetWindowRect(m_hwindow, &r);
        MoveWindow(m_hwindow, x, y, r.right - r.left, r.bottom - r.top, TRUE);
    }

	int WindowWin::Update(int dt) {	

		MSG msg;
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
		e.elapsed_time_s = (double)dt / 1000.0;
		OnIdleEvent(e);
		return 1;
	}

    int WindowWin::Loop()
    {
        m_timer->Reset();

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
            e.elapsed_time_s = m_timer->GetElapsedSeconds();
            m_timer->Reset();
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

    const Core::String WindowWin::GetTitle() const {
        wchar_t buf[256];
        GetWindowTextW(m_hwindow, buf, 256);
        return Core::String(buf);
    }

    void WindowWin::Quite() {
        SendMessageW(m_hwindow, WM_DESTROY, 0, 0);
    }

    HWND WindowWin::GetNativeHandle() {
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
            x = LOWORD(lParam);
            y = HIWORD(lParam);

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
            GetKeyboard()->SetKeyState((int)wParam, true);
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
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)a);
			SetWindowLong(hwnd, GWL_STYLE, WS_CHILD | WS_DLGFRAME);
            a->OnWindowCreated();
        }
            break;
		//case WM_SHOWWINDOW:
		//{
		//	HWND parent = GetAncestor(hwnd, GA_PARENT);
		//	if (parent) {
		//		RECT r;
		//		GetClientRect(parent, &r);
		//		auto w = r.right - r.left;
		//		auto h = r.bottom - r.top;								
		//		MoveWindow(hwnd, 0, 0, w, h, TRUE);
		//	}
		//	SetWindowLong(hwnd, GWL_STYLE, WS_CHILD | WS_DLGFRAME);
		//}
		//	break;
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

    void WindowWin::InternalCreate() {

		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hInstance = GetModuleHandle(0);
		wc.lpfnWndProc = WindowCallBack;
		wc.lpszClassName = TEXT("PunkEngine");
		wc.lpszMenuName = 0;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		RECT rect;
		rect.left = m_window_description.m_x;
		rect.right = m_window_description.m_x + m_window_description.m_width;
		rect.top = m_window_description.m_y;
		rect.bottom = m_window_description.m_y + m_window_description.m_height;

		if (!RegisterClass(&wc))
			throw Error::InvalidArgumentException(L"Can't register window class");

		DWORD style = 0;
		DWORD styleEx = 0;
		DWORD x = CW_USEDEFAULT;
		DWORD y = CW_USEDEFAULT;
		DWORD width = CW_USEDEFAULT;
		DWORD height = CW_USEDEFAULT;

        if (m_window_description.parent_wnd) {
            m_use_parent_window = true;            

			style = WS_CHILD | WS_DLGFRAME;
			RECT r;
			GetClientRect(m_window_description.parent_wnd, &r);
			width = r.right - r.left;
			height = r.bottom - r.top;

        }
        else {
            m_use_parent_window = false;                        

            style = WS_OVERLAPPEDWINDOW;
            styleEx = 0;

            AdjustWindowRectEx(&rect, style, false, styleEx);            

			DWORD x = 0;
			DWORD y = 0;
			DWORD width = rect.right - rect.left;
			DWORD height = rect.bottom - rect.top;
        }

		m_hwindow = CreateWindow(TEXT("PunkEngine"), NULL, style,
			x, y, width, height, m_window_description.parent_wnd, 0,
			GetModuleHandle(0), (void*)this);				

		if (!m_hwindow)
			throw Error::InvalidArgumentException(L"Can't create window");

		GetClientRect(m_hwindow, &rect);
		ShowWindow(m_hwindow, SW_SHOW);
		UpdateWindow(m_hwindow);
    }

    void WindowWin::InternalDestroy() {
        PostQuitMessage(0);
    }
}
PUNK_ENGINE_END

#endif	//	_WIN32
