#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <images/module.h>
#include <system/factory/module.h>
#include <attributes/terrain/iterrain_data_provider.h>
#include <graphics/primitives/vertex.h>

using namespace Punk::Engine;
using namespace Punk::Engine::Graphics;

class VertexTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(VertexTest);
	CPPUNIT_TEST(test1);
	CPPUNIT_TEST_SUITE_END();
public:

	void test1() {
		Vertex<VertexComponent::Position> vertex;
		CPPUNIT_ASSERT(sizeof(vertex) == 4 * 4);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(VertexTest);
