#include <iostream>
#include <punk_engine.h>

using namespace Punk::Engine;

void LoadBasicModules() {
	std::vector<Core::String> modules{ { L"punk_graphics", L"punk_loader", L"punk_scene", L"punk_attributes", L"punk_ai", L"punk_application", L"punk_core",
		L"punk_error", L"punk_font", L"punk_image",
		L"punk_math", L"punk_render", L"punk_string", L"punk_system",
		L"punk_animator" } };

	for (auto& module : modules) {
		try{
			System::LoadModule(module);
			System::GetDefaultLogger()->Info("Module loaded '" + module + "'");
		}
		catch (System::Error::SystemException& e) {
			System::GetDefaultLogger()->Error("Can't load " + module + ". " + e.Message() + ". " + e.GetStack());
		}
		catch (...) {
			System::GetDefaultLogger()->Error("Can't load " + module);
		}
	}
}

int main(int argc, char** argv)
{
	LoadBasicModules();

	try{
		if (argc < 3) {
			std::cout << "txt2bin --input input --output output" << std::endl;
			return 0;
		}

		Core::String input;
		Core::String output;
		for (int i = 0; i < argc; ++i) {
			if (!strcmp(argv[i], "--input")) {
				input = argv[i + 1];
				++i;
				continue;
			}
			if (!strcmp(argv[i], "--output")) {
				output = argv[i + 1];
				++i;
				continue;
			}
		}

		auto module = System::LoadModule("punk_loader");
		if (!module) {
			std::cout << "Failed to load loader module" << std::endl;
			return 0;
		}

		auto io_module = Core::QueryInterfacePtr<IoModule::IIoModule>(module, IoModule::IID_IIoModule);
		if (!io_module)
		{
			std::cout << "Failed to query io module interface from loaded module" << std::endl;
			return 0;
		}

		auto object = io_module->Parse(input);
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

    return 0;
}
