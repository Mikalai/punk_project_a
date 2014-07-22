#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <math/min_max.h>

using namespace Punk::Engine;

class MinMaxTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MinMaxTest);
	CPPUNIT_TEST(testMin);
	CPPUNIT_TEST(testMax);
	CPPUNIT_TEST_SUITE_END();
public:
	void testMin() {
		int a = 1;
		int b = 2;
		int c = 3;
		CPPUNIT_ASSERT(1 == Math::Min(a, b));
		CPPUNIT_ASSERT(1 == Math::Min(b, a));
		CPPUNIT_ASSERT(1 == Math::Min(a, b, c));
		CPPUNIT_ASSERT(1 == Math::Min(a, c, b));
		CPPUNIT_ASSERT(1 == Math::Min(b, a, c));
		CPPUNIT_ASSERT(1 == Math::Min(b, c, a));
		CPPUNIT_ASSERT(1 == Math::Min(c, b, a));
		CPPUNIT_ASSERT(1 == Math::Min(c, a, b));
	}

	void testMax() {
		int a = 1;
		int b = 2;
		int c = 3;
		CPPUNIT_ASSERT(2 == Math::Max(a, b));
		CPPUNIT_ASSERT(2 == Math::Max(b, a));
		CPPUNIT_ASSERT(3 == Math::Max(a, b, c));
		CPPUNIT_ASSERT(3 == Math::Max(a, c, b));
		CPPUNIT_ASSERT(3 == Math::Max(b, a, c));
		CPPUNIT_ASSERT(3 == Math::Max(b, c, a));
		CPPUNIT_ASSERT(3 == Math::Max(c, b, a));
		CPPUNIT_ASSERT(3 == Math::Max(c, a, b));
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION(MinMaxTest);
