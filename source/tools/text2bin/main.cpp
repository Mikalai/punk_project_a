#include <iostream>
#include <punk_engine.h>

using namespace Punk::Engine;

Core::String g_path;
Core::Pointer<IoModule::IIoModule> g_io_module;

void LoadBasicModules() {
	std::vector<Core::String> modules{ { L"punk_graphics", L"punk_loader", L"punk_scene", L"punk_attributes", L"punk_ai", L"punk_application", L"punk_core",
		L"punk_error", L"punk_font", L"punk_image",
		L"punk_math", L"punk_render", L"punk_string", L"punk_system",
		L"punk_animator" } };

	for (auto& module : modules) {
		try{
			System::LoadPunkModule(module);
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

bool ReplaceEntityNames(Core::Pointer<SceneModule::INode> node) {
	for (std::uint32_t i = 0, max_i = node->GetAttributesCount(); i < max_i; ++i) {
		auto attribute = node->GetAttribute(i);
		auto file_stub = Core::QueryInterfacePtr<Attributes::IFileStub>(attribute->GetRawData(), Attributes::IID_IFileStub);
		if (file_stub) {
			auto filename = file_stub->GetFilename();
			auto name = filename.Split(".");			
			name[name.Size() - 1] = L"b" + name[name.Size() - 1];
			file_stub->SetFilename(name.ToString("."));
		}
	}
	return false;
}

bool ConvertDependencies(Core::Pointer<SceneModule::INode> node) {
	for (std::uint32_t i = 0, max_i = node->GetAttributesCount(); i < max_i; ++i) {
		auto attribute = node->GetAttribute(i);
		auto file_stub = Core::QueryInterfacePtr<Attributes::IFileStub>(attribute->GetRawData(), Attributes::IID_IFileStub);
		if (file_stub) {
			auto object = g_io_module->Parse(g_path + file_stub->GetFilename());
			auto filename = file_stub->GetFilename();
			auto name = filename.Split(".");
			name[name.Size() - 1] = L"b" + name[name.Size() - 1];
			g_io_module->Serialize(object, g_path + name.ToString("."));			
		}
	}
	return false;
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
		Core::String path;
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
			if (!strcmp(argv[i], "--path")) {
				g_path = path = argv[i + 1];
				++i;
				continue;
			}
		}

		auto module = Core::Pointer < System::IModule > { System::LoadPunkModule("punk_loader"), Core::DestroyObject};
		if (!module) {
			std::cout << "Failed to load loader module" << std::endl;
			return 0;
		}

		g_io_module = Core::QueryInterfacePtr<IoModule::IIoModule>(module, IoModule::IID_IIoModule);
		if (!g_io_module)
		{
			std::cout << "Failed to query io module interface from loaded module" << std::endl;
			return 0;
		}

		auto object = g_io_module->Parse(path + input);

		auto scene = Core::QueryInterfacePtr<SceneModule::IScene>(object, SceneModule::IID_IScene);
		if (scene) {
			scene->Traverse(ConvertDependencies);
			scene->Traverse(ReplaceEntityNames);
		}

		g_io_module->Serialize(object, g_path + output);
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
