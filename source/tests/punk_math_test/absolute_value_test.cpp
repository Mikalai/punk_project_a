#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <math/absolute_value.h>

using namespace Punk::Engine;

class AbsoluteValueTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AbsoluteValueTest);
	CPPUNIT_TEST(testAbs);
	CPPUNIT_TEST_SUITE_END();
public:
	void testAbs() {
		CPPUNIT_ASSERT(1 == Math::Abs(-1));
		CPPUNIT_ASSERT(1 == Math::Abs(1));
		CPPUNIT_ASSERT(1.0 == Math::Abs(1.0));
		CPPUNIT_ASSERT(1.0 == Math::Abs(-1.0));
		CPPUNIT_ASSERT(1.0f == Math::Abs(-1.0f));
		CPPUNIT_ASSERT(1.0f == Math::Abs(1.0f));
	}	
};


CPPUNIT_TEST_SUITE_REGISTRATION(AbsoluteValueTest);
