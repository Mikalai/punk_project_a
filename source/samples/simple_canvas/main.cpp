#include <stdlib.h>
#include <stdio.h>
#include <string/module.h>
#include <system/module.h>
#include <core/module.h>
#include <error/module.h>
#include <graphics/module.h>

using namespace Punk::Engine;

void f(const System::MouseEvent& e) {    
    System::GetDefaultLogger()->Info(e.ToString());
}

int main() {
    try {
        Graphics::CanvasDescription desc;
        Graphics::ICanvas* canvas = Graphics::CreateCanvas(desc);
        System::IWindow* wnd = dynamic_cast<System::IWindow*>(canvas);
        f(System::MouseEvent());        
        wnd->SubscribeMouseEvent(f);
        wnd->Open();
        wnd->Loop();
        Graphics::DestroyCanvas(canvas);
    }
    catch(System::Error::SystemException& e) {
        System::GetDefaultLogger()->Error(e.Message());
        MessageBoxW(0, (LPCWSTR)e.Message().ToWchar().Data(), L"Error", MB_OK|MB_ICONERROR);
    }
}
