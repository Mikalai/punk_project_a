#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <string/module.h>
#include <system/module/module.h>

int main()
{
	try
	{
		Punk::Engine::System::LoadPunkModule("punk_attributes");
		Punk::Engine::System::LoadPunkModule("punk_image");
		CppUnit::TextUi::TestRunner runner;
		CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
		runner.addTest(registry.makeTest());
		runner.run();
	}
	catch (Punk::Engine::Core::Error::Exception& e)
	{
		std::wcout << e.GetCode() << std::endl;
	}
	return 0;
}
