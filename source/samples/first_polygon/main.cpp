#include <stdlib.h>
#include <stdio.h>
#include <error/module.h>
#include <stdlib.h>
#include <stdio.h>
#include <punk_engine.h>

int main() {
	using namespace Punk::Engine;
	
	try{
        Core::Pointer<System::IModule> punk_application = System::LoadModule("punk_application");
        if (!punk_application)
            throw System::Error::SystemException("Can't load punk_application module");

        auto app = System::CreateInstancePtr<Runtime::IApplication>(Runtime::CLSID_Application, Runtime::IID_IApplication);

		if (!app) {
			System::GetDefaultLogger()->Error("Can't create application");
			return -1;
		}
		
		auto options = System::CreateInstancePtr<Punk::Engine::Attributes::IOptions>(
			Punk::Engine::Attributes::CLSID_Options, Punk::Engine::Attributes::IID_IOptions);

#ifdef WIN32
		options->SetDataPath(L"c:\\Projects\\game\\dev\\punk_project_a\\data\\maps\\map1\\");		
#elif defined __linux__
		options->SetDataPath(L"/home/mikalaj/Projects/punk_project_a/data/maps/map1/");
#endif
		app->GetSceneManager()->GetScene()->GetRoot()->Set<Punk::Engine::Attributes::IOptions>(L"Options", options);

		auto file = System::CreateInstancePtr<Punk::Engine::Attributes::IFileStub>(Punk::Engine::Attributes::CLSID_FileStub, Punk::Engine::Attributes::IID_IFileStub);
#ifdef WIN32
        file->SetFilename("level_1.pmd");
#elif defined __linux__
        file->SetFilename("level_1.pmd");
#endif

		app->GetSceneManager()->GetScene()->GetRoot()->Set<Punk::Engine::Attributes::IFileStub>("LevelFile", file);

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
