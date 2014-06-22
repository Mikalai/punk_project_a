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
#include "config.h"
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace System
{
    enum class WindowSystem { Windows, X11 };

    struct PUNK_ENGINE_API WindowDescription
    {
#ifdef _WIN32
        WindowSystem system {WindowSystem::Windows};
        bool use_parent_window {false};
        HWND parent_wnd {0};
#elif defined __gnu_linux__

#endif
        Core::String m_name;
        unsigned m_x {100};
        unsigned m_y {100};
        unsigned m_width {1024};
        unsigned m_height {768};
    };
}
PUNK_ENGINE_END

#endif // WINDOW_DESCRIPTION_H
