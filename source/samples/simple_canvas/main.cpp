#include <stdlib.h>
#include <stdio.h>
#include <string/module.h>
#include <system/module.h>
#include <core/module.h>
#include <error/module.h>
#include <graphics/module.h>

using namespace Punk::Engine;

static Graphics::ICanvas* canvas;

void f(const System::IdleEvent& e) {
    static Graphics::IVideoDriver* driver;
    if (!driver)
        driver = canvas->GetVideoDriver();
    static Graphics::IFrameBuffer* buffer;
    if (!buffer)
        buffer = Graphics::GetBackbuffer();
    buffer->Bind();
    buffer->SetClearColor(0, 0, 1, 0);
    buffer->SetClearFlag(true, true, true);
    buffer->Clear();
    buffer->Unbind();
    canvas->SwapBuffers();
}

int main() {
    try {        
        canvas = Graphics::CreateCanvas(Graphics::CanvasDescription());
        auto wnd = canvas->GetWindow();
        wnd->SubscribeIdleEvent(f);
        wnd->Open();
        wnd->Loop();
        delete wnd;
    }
    catch(System::Error::SystemException& e) {
        MessageBoxW(0, (LPCWSTR)e.Message().ToWchar().Data(), L"Error", MB_OK|MB_ICONERROR);
    }
}
