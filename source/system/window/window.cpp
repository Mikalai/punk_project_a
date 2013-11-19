#include "window.h"
#include "win32_window.h"
#include "x11_window.h"

namespace System
{
    PUNK_OBJECT_REG(Window, "System.Object", typeid(Window).hash_code(), nullptr, nullptr, &Object::Info.Type);

    Window::Window()
    {
        Info.Add(this);
    }

    Window::~Window()
    {
        Info.Remove(this);
    }

    Window* CreateRootWindow(const WindowDesc &desc)
    {
#ifdef _WIN32
        if (desc.system == WindowSystem::Windows)
            return new WindowWin(desc);
#elif defined __gnu_linux__
        if (desc.system == WindowSystem::X11)
            return new WindowX11(desc);
#endif
        return nullptr;
    }
}
