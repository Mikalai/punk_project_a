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

using Punk::Engine;

int main() {
    Punk::Engine::Scene::ISceneGraph* scene = Punk::Engine::Scene::CreateSceneFromFile("c:\\Users\\mikal_000\\SkyDrive\\projects\\game\\dev\\punk_project_a\\data\\maps\\map1\\level_1.pmd");

    Loader::LoaderGraphProcessor proc = new Loader::LoaderGraphProcessor;
    proc->Initialize(scene);
}
