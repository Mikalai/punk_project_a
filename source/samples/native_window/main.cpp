#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "system/module.h"
#include "core/module.h"

using namespace Punk::Engine;

void f(const System::MouseEvent& e) {
    if (e.leftButton)
        system("notify-send [\"MouseEvent\"] \"This is a mouse event\"");
}

int main() {
    f(System::MouseEvent());
    System::Window* wnd = Core::Acquire<System::Window>("window", "default_window", "window");
    wnd->OnMouseEvent.Add(f);
    wnd->Loop();
    System::IKeyBoard* keyboard = Core::Acquire<System::IKeyBoard>("input", "default_keyboard", "keyboard");
    Core::Release("input", "default_keyboard");
    Core::Release("window", "default_window");
}
