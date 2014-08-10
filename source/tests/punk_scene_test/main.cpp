#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <string/module.h>

int main()
{
	try
	{
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
