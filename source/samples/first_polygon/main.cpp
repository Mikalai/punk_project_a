#include <stdlib.h>
#include <stdio.h>
#include <string/module.h>
#include <system/module.h>
#include <math/module.h>
#include <core/module.h>
#include <error/module.h>
#include <graphics/module.h>

using namespace Punk::Engine;

static System::Thread thread;
static bool g_flag = true;
static Graphics::ICanvas* canvas;
static Graphics::IVideoDriver* driver;
static Graphics::IFrameBuffer* buffer;
static Graphics::IRender* render;

void f(const System::IdleEvent& e) {
    buffer->Bind();
    buffer->SetViewport(0, 0, 1024, 768);
    buffer->SetClearColor(0, 0, 1, 0);
    buffer->SetClearFlag(true, true, true);
    buffer->Clear();
    render->AsyncBeginRendering(buffer);
    buffer->Unbind();
    canvas->SwapBuffers();
}

void OnExit() {
    g_flag = false;
    thread.Join();
}

unsigned PUNK_STDCALL RenderFunc(void* data) {
    while (g_flag) {
        Graphics::IRender* render = (Graphics::IRender*)data;
        Graphics::IFrameUniquePtr frame = Graphics::CreateFrame(render);
        frame->SetWorldMatrix(Math::CreateIdentity());
        frame->SetViewMatrix(Math::CreateIdentity());
        frame->SetProjectionMatrix(Math::CreateOrthographicProjection(0, 1024, 0, 768, -1, 1));
        frame->DrawLine(100, 100, 200, 200);
        frame->DrawLine(200, 200, 300, 100);
        frame->DrawLine(300, 100, 100, 100);
        frame->DrawQuad(400, 100, 100, 100);
        System::GetDefaultLogger()->Info("Draw");
        render->WaitEndRendering();
    }
}

void Start()
{
    canvas = Graphics::CreateCanvas(Graphics::CanvasDescription());
    auto wnd = canvas->GetWindow();
    wnd->SubscribeIdleEvent(f);
    wnd->SubscribeWindowDestroyEvent(OnExit);
    wnd->Open();

    if (!driver)
        driver = canvas->GetVideoDriver();

    if (!buffer)
        buffer = Graphics::GetBackbuffer();

    if (!render)
        render = Graphics::CreateRender(driver).release();

    thread.Create(RenderFunc, (void*)render);

    wnd->Loop();
    delete wnd;
}

int main() {
    try {
        Start();
    }
    catch(System::Error::SystemException& e) {
        System::GetDefaultLogger()->Error(e.Message());
        MessageBoxW(0, (LPCWSTR)e.Message().ToWchar().Data(), L"Error", MB_OK|MB_ICONERROR);
    }
}
