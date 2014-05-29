#include <stdlib.h>
#include <stdio.h>
#include <error/module.h>
#include <stdlib.h>
#include <stdio.h>
#include <string/module.h>
#include <system/module.h>
#include <math/module.h>
#include <core/module.h>
#include <error/module.h>
#include <scene/singlethreaded/module.h>
#include <application/iapplication.h>

using namespace Punk::Engine;

//static System::Thread thread;
//static bool g_flag = true;
//static Graphics::ICanvas* canvas;
//static Graphics::IVideoDriver* driver;
//static Graphics::IFrameBuffer* buffer;
//static Graphics::ILowLevelRender* render;
//
//void f(const System::IdleEvent& e) {
//    buffer->Bind();
//    buffer->SetViewport(0, 0, 1024, 768);
//    buffer->SetClearColor(0, 0, 1, 0);
//    buffer->SetClearFlag(true, true, true);
//    buffer->Clear();
//    render->AsyncBeginRendering(buffer);
//    buffer->Unbind();
//    canvas->SwapBuffers();
//}
//
//void OnExit() {
//    g_flag = false;
//    thread.Join();
//}
//
//unsigned PUNK_STDCALL RenderFunc(void* data) {
//    while (g_flag) {
//        Graphics::ILowLevelRender* render = (Graphics::ILowLevelRender*)data;
//        Graphics::IFrameUniquePtr frame = Graphics::CreateFrame(render);
//        frame->SetWorldMatrix(Math::CreateIdentity());
//        frame->SetViewMatrix(Math::CreateIdentity());
//        frame->SetProjectionMatrix(Math::CreateOrthographicProjection(0, 1024, 0, 768, -1, 1));
//        frame->DrawLine(100, 100, 200, 200);
//        frame->DrawLine(200, 200, 300, 100);
//        frame->DrawLine(300, 100, 100, 100);
//        frame->DrawQuad(400, 100, 100, 100);
//        System::GetDefaultLogger()->Info("Draw");
//        render->WaitEndRendering();
//    }
//}
//
//void Start()
//{
//    canvas = Graphics::CreateCanvas(Graphics::CanvasDescription());
//    auto wnd = canvas->GetWindow();
//    wnd->SubscribeIdleEvent(f);
//    wnd->SubscribeWindowDestroyEvent(OnExit);
//    wnd->Open();
//
//    if (!driver)
//        driver = canvas->GetVideoDriver();
//
//    if (!buffer)
//        buffer = Graphics::GetBackbuffer();
//
//	if (!render)
//		render = driver->GetRender();
//
//    thread.Create(RenderFunc, (void*)render);
//
//    wnd->Loop();
//    delete wnd;
//}
//
//int main() {
//    try {
//        Start();
//    }
//    catch(System::Error::SystemException& e) {
//        System::GetDefaultLogger()->Error(e.Message());
//        MessageBoxW(0, (LPCWSTR)e.Message().ToWchar().Data(), L"Error", MB_OK|MB_ICONERROR);
//    }
//}

int main() {

	try{
		System::LoadModule("punk_application");
		Runtime::IApplication* app{ nullptr };
		Core::GetFactory()->CreateInstance(Runtime::IID_IApplication, (void**)&app);

		if (!app) {
			System::GetDefaultLogger()->Error("Can't create application");
			return -1;
		}

		Core::IObject* o = nullptr;
		app->QueryInterface(Core::IID_IObject, (void**)&o);

		app->Run();
	}
	catch (System::Error::SystemException& e) {
		System::GetDefaultLogger()->Error(e.Message() + " at \n" + e.GetStack());
	}
	catch (Core::Error::CoreException& e) {
		System::GetDefaultLogger()->Error(e.GetData());
	}
	catch (Core::Error::Exception& e) {
		System::GetDefaultLogger()->Error("Fatal error");
	}
}