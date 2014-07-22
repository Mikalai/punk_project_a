#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <math/square_root.h>
#include <math/triangle.h>

using namespace Punk::Engine;
using namespace Punk::Engine::Math;

class TriangleTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TriangleTest);
	CPPUNIT_TEST(testTriangleData);
	CPPUNIT_TEST(testTriangleAccessorBase);
	CPPUNIT_TEST(testTriangleAccessor);
	CPPUNIT_TEST(testTriangleOperationsBase);
	CPPUNIT_TEST(testTriangle3DOperations);
	CPPUNIT_TEST(testTriangle2DOperations);
	CPPUNIT_TEST_SUITE_END();
public:

	void testTriangleData() {
	}

	void testTriangleAccessorBase() {
	}

	void testTriangleAccessor() {
	}

	void testTriangleOperationsBase() {
	}

	void testTriangle3DOperations() {
	}

	void testTriangle2DOperations() {
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION(TriangleTest);
