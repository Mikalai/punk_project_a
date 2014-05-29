#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <error/module.h>
#include <stdlib.h>
#include <stdio.h>
#include <string/module.h>
#include <system/module.h>
#include <math/module.h>
#include <core/module.h>
#include <error/module.h>
#include <scene/module.h>
#include <application/iapplication.h>

using namespace Punk::Engine;

//void f(){
//	SceneModule::ISceneGraphUniquePtr scene = Punk::Engine::SceneModule::CreateSceneFromFile("c:\\Projects\\game\\dev\\punk_project_a\\data\\maps\\map1\\", "level_1.pmd");
//	Loader::IoObserver* proc = new Loader::IoObserver;
//	LowLevelRender::RenderProcessor* render_proc = new LowLevelRender::RenderProcessor;
//
//	System::ITimerUniquePtr timer = System::CreateTimer();
//
//	render_proc->SetGraph(scene.get());
//	proc->SetGraph(scene.get());
//	render_proc->StartProcessing();
//	proc->StartProcessing();
//
//	render_proc->Show();
//
//	while (1)
//	{
//		timer->Reset();
//		int dt = timer->GetElapsedMiliseconds();
//		render_proc->BeginUpdate(dt);
//		proc->BeginUpdate(dt);
//		proc->WaitUpdateFinish();
//		render_proc->WaitUpdateFinish();
//	}
//
//	proc->StopProcessing();
//	render_proc->StopProcessing();
//	proc->WaitProcessingComplete();
//	render_proc->WaitProcessingComplete();
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
