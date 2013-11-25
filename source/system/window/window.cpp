#include "window.h"
#include "win32_window.h"
#include "x11_window.h"

PUNK_ENGINE_BEGIN
namespace System
{
    Core::Rtti Window::Type{"Punk.Engine.System.Window", typeid(Window).hash_code(), {&Core::Object::Type}};

    Window::Window()
    {
        CREATE_INSTANCE(Window);
    }

    Window::~Window()
    {
        DESTROY_INSTANCE();
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
PUNK_ENGINE_END
