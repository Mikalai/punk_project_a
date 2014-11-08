#include <iostream>

int main() {
	std::cout << "Hello world!" << std::endl;
}

















//#include <string>
//#include <iostream>
//#include <thread>
//#include <sstream>
//#include <map>
//#include <string/module.h>
//#include <system/factory/module.h>
//#include <system/module/module.h>
//#include <core/pointer.h>
//#include <core/iobject.h>
//#include <core/imeta_interface.h>
//
//using namespace Punk::Engine;
//
//std::map < Core::String, Core::Pointer<Core::IObject>> g_objects;
//
//void func(const Core::String& command) {
//	Core::StringList cmd = command.Split(" ");
//	//std::wcout << L"Command: " << cmd[0].toStdWString() << ", count: " << cmd.Size() << std::endl;
//	if (cmd[0] == "q" || cmd[0] == "quit") {
//		std::exit(0);
//	}
//
//	if (cmd[0] == "factory") {
//		auto f = System::GetFactory();
//		if (cmd[1] == "count") {
//			std::cout << f->GetCreatorsCount() << std::endl;
//		}
//		if (cmd[1] == "list") {
//			auto count = f->GetCreatorsCount();
//			for (auto i = 0; i < count; ++i) {
//				std::wcout << L"Creator[" << i << L"] " << f->GetCreatorName(i).toStdWString() << L" " << f->GetCreatorGuid(i).ToString().toStdWString() << std::endl;
//			}
//		}
//		if (cmd[1] == "get_guid") {
//			auto name = cmd[2];
//			auto g = f->GetCreatorGuid(name);
//			std::wcout << g.ToString().toStdWString() << std::endl;
//		}
//		if (cmd[1] == "create") {
//			auto clsid = cmd[2];
//			auto name = cmd[3];
//			auto g = f->GetCreatorGuid(clsid);
//			auto it = g_objects.find(name);
//			g_objects[name] = System::CreateInstancePtr<Core::IObject>(g, Core::IID_IObject);
//		}
//	}
//	if (cmd[0] == "invoke") {
//		auto method = cmd[1];
//		auto object = cmd[2];
//		Core::Buffer args;
//		for (int i = 3; i < cmd.Size(); ++i) {
//			args.WriteString(cmd[i]);
//		}
//		auto it = g_objects.find(object);
//		if (it == g_objects.end()) {
//			System::GetDefaultLogger()->Error("Can't invoke method from null reference object");
//			return;
//		}
//		auto meta = Core::QueryInterfacePtr<Core::IMetaInterface>(it->second, Core::IID_IMetaInterface);
//		if (!meta.get()) {
//			System::GetDefaultLogger()->Error("Object '" + object + "' doesn't support meta interface");
//			return;
//		}
//		meta->Invoke(method, args);
//		auto count = args.ReadUnsigned32();
//		for (int i = 0; i < count; ++i) {
//			std::wcout << args.ReadString().toStdWString() << std::endl;
//		}
//	}
//	if (cmd[0] == "load") {
//		auto mode = cmd[1];
//		if (mode.ToLower() == "module") {
//			auto module = cmd[2];
//			System::LoadPunkModule(module);
//		}
//	}
//}
//
//int main()
//{
//	std::string s;
//	std::cout << std::string(60, '*') << std::endl;
//	std::cout << "*" << "\tWelcome to PunkEngine console interpretator" << std::endl;
//	std::cout << std::string(60, '*') << std::endl;
//
//	std::stringstream stringstream{ "factory create CLSID_Timer timer1 \n\
//invoke reset timer1 \n\
//invoke getelapsedmiliseconds timer1\n\
//q" };
//	std::istream& stream = stringstream;
//	do {
//		std::cout << "> ";
//		std::getline(stream, s);
//
//		if (s.find_first_of("~") == 0) {
//			std::thread t{ func, Core::String(s.c_str()) };
//			t.detach();
//		}
//		else {
//			func(Core::String(s.c_str()));
//		}
//	} while (true);
//}