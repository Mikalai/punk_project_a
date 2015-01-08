#include <core/action.h>

using namespace Punk::Engine::Core;

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ActionTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ActionTest);
	CPPUNIT_TEST(test1);
	CPPUNIT_TEST(test2);
	CPPUNIT_TEST_SUITE_END();

public:

	void test1() {

		ActionSlot<void> slot;
		int i = 0;
		slot.Add([&i](){
			++i;
		});

		slot();

		CPPUNIT_ASSERT(i == 1);
	}

	void test2() {
		ActionSlot<int> slot;
		int i = 0;
		slot.Add([&i](int k){
			i = k;
		});

		slot(2);

		CPPUNIT_ASSERT(i == 2);
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION(ActionTest);
