#include <cppunit/TestFixture.h>
#include <thread>
#include <cppunit/extensions/HelperMacros.h>

#include <scene/module.h>
#include <system/factory/module.h>
#include <string/module.h>
#include <core/module.h>

#include <system/time/module.h>

//#pragma comment(lib, "punk_scene.lib")


using namespace Punk::Engine;

class ImpulseGeneratorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ImpulseGeneratorTest);
	CPPUNIT_TEST(test1);
	CPPUNIT_TEST_SUITE_END();
public:

	void Action(std::uint32_t v) {
		m_v++;
		std::cout << "Action triggered " << m_v << ". Delta " << v << std::endl;
	}

	void test1() {
			{
				auto action = new Core::Action<ImpulseGeneratorTest, std::uint32_t>(this, &ImpulseGeneratorTest::Action);
				auto ptr = System::ImpulsedAction(action, Core::DestroyObject);
				auto instance = System::IImpulseGenerator::Instance();
				instance->AddAction(0, ptr, true);
				std::this_thread::sleep_for(std::chrono::system_clock::duration(100000000));
			}
		System::IImpulseGenerator::Destroy();
	}

	int m_v{ 0 };
};

CPPUNIT_TEST_SUITE_REGISTRATION(ImpulseGeneratorTest);
