#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdlib.h>
#include <stdio.h>
#include <string/module.h>
#include <system/module.h>
#include <math/module.h>
#include <core/module.h>
#include <error/module.h>
#include <graphics/module.h>
#include <scene/module.h>
#include <loader/module.h>
#include <render/module.h>

using namespace Punk::Engine;

void f(){
	Scene::ISceneGraphUniquePtr scene = Punk::Engine::Scene::CreateSceneFromFile("c:\\Projects\\game\\dev\\punk_project_a\\data\\maps\\map1\\", "level_1.pmd");
	Loader::LoaderGraphProcessor* proc = new Loader::LoaderGraphProcessor;
	Render::RenderProcessor* render_proc = new Render::RenderProcessor;

	System::ITimerUniquePtr timer = System::CreateTimer();

	render_proc->SetGraph(scene.get());
	proc->SetGraph(scene.get());
	render_proc->StartProcessing();
	proc->StartProcessing();

	render_proc->Show();

	while (1)
	{
		timer->Reset();
		int dt = timer->GetElapsedMiliseconds();
		render_proc->BeginUpdate(dt);
		proc->BeginUpdate(dt);
		proc->WaitUpdateFinish();
		render_proc->WaitUpdateFinish();
	}

	proc->StopProcessing();
	render_proc->StopProcessing();
	proc->WaitProcessingComplete();
	render_proc->WaitProcessingComplete();
}
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int();
	f();	
}
