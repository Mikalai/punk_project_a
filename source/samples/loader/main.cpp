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

using namespace Punk::Engine;

int main() {
    Scene::ISceneGraphUniquePtr scene = Punk::Engine::Scene::CreateSceneFromFile("c:\\Projects\\game\\dev\\punk_project_a\\data\\maps\\map1\\level_1.pmd");
    Loader::LoaderGraphProcessor* proc = new Loader::LoaderGraphProcessor;
    proc->SetGraph(scene.get());
    proc->StartProcessing();
    System::Window* wnd = System::CreateRootWindow(System::WindowDescription());
    wnd->Open();
    wnd->Loop();
    proc->StopProcessing();
    proc->WaitProcessingComplete();
}
