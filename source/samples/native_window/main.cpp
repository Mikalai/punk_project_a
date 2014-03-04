#include <stdlib.h>
#include <stdio.h>
#include <string/module.h>
#include <system/module.h>
#include <core/module.h>
#include <error/module.h>

using namespace Punk::Engine;

void f(const System::MouseEvent& e) {    
    System::GetDefaultLogger()->Info(e.ToString());
}

int main() {
    try {
        f(System::MouseEvent());
        System::WindowDescription desc;
        auto wnd = System::CreateRootWindow(desc);
        wnd->SubscribeMouseEvent(f);
        wnd->Open();
        wnd->Loop();
        delete wnd;
    }
    catch(System::Error::SystemException& e) {
        MessageBoxW(0, (LPCWSTR)e.Message().ToWchar().Data(), L"Error", MB_OK|MB_ICONERROR);
    }
}
