#ifndef WINDOW_DESCRIPTION_H
#define WINDOW_DESCRIPTION_H

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif	//	NOMINMAX
#include <Windows.h>
#elif defined __gnu_linux__
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xutil.h>
#endif

namespace System
{
    enum class WindowSystem { Windows, X11 };

    struct WindowDesc
    {
#ifdef _WIN32
        WindowSystem system {WindowSystem::Windows};
        bool use_parent_window {false};
        HWND parent_wnd {0};
#elif defined __gnu_linux__
        WindowSystem system {WindowSystem::X11};
#endif
        unsigned m_x {100};
        unsigned m_y {100};
        unsigned m_width {1024};
        unsigned m_height {768};
    };
}
#endif // WINDOW_DESCRIPTION_H
