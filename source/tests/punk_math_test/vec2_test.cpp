#include <math/forward.h>
#include <math/tuple.h>
#include "string/string.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace Punk::Engine::Math;
using namespace Punk::Engine::Core;

class Vector2Test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Vector2Test);
	CPPUNIT_TEST(testXYRG);
	CPPUNIT_TEST(testIndex);
	CPPUNIT_TEST(testVector2);
	CPPUNIT_TEST(testNormalize);
	CPPUNIT_TEST(testLength);
	CPPUNIT_TEST(testSqrLength);
	CPPUNIT_TEST(testNegate);
	CPPUNIT_TEST(testSet);
	CPPUNIT_TEST(testComponentMult);
	CPPUNIT_TEST(testDot);
	CPPUNIT_TEST(testToString);
	CPPUNIT_TEST_SUITE_END();
public:
	void testXYRG() {
		TupleData<float, 2, tagVector> vv{ { 1, 2 } };
		TupleComponentAccessorBase<float, 2, tagVector> vvv{ { 1, 2 } };
		vvv[0] = 1;
		vec2 v{ 1, 2 };
		CPPUNIT_ASSERT(v.X() == 1);
		CPPUNIT_ASSERT(v.Y() == 2);
		CPPUNIT_ASSERT(v.XY() == vec2(1, 2));
		CPPUNIT_ASSERT(v.YX() == vec2(2, 1));
	}

	void testIndex()
	{
		vec2 v{ 1, 2 };
		CPPUNIT_ASSERT(v[0] == 1);
		CPPUNIT_ASSERT(v[1] == 2);
	}

	void testVector2()
	{
		vec2 v1{ 1, 2 };
		vec2 v2(1, 2);
		CPPUNIT_ASSERT(v1 == v2);
		vec2 v3(v1);
		CPPUNIT_ASSERT(v3 == v1);
		v1 = v2;
		CPPUNIT_ASSERT(v1 == v2);
	}

	void testNormalize()
	{
		vec2 v{ 5, 0 };
		vec2 v2 = v.Normalized();
		CPPUNIT_ASSERT(v2 == vec2(1, 0));
		v.Normalize();
		CPPUNIT_ASSERT(v == vec2(1, 0));
	}

	void testLength()
	{
		vec2 v{ 3, 4 };
		float l = v.Length();
		CPPUNIT_ASSERT(l == 5);
	}

	void testSqrLength()
	{
		vec2 v{ 3, 4 };
		float l = v.Length();
		CPPUNIT_ASSERT(l == 5.0f);
	}

	void testNegate()
	{
		vec2 v1{ 3, 4 };
		vec2 v2 = v1.Negated();
		CPPUNIT_ASSERT(v2 == vec2(-3, -4));
		vec2 v3 = -v1;
		CPPUNIT_ASSERT(v3 == vec2(-3, -4));
	}

	void testSet()
	{
		vec2 v;
		v.Set(1, 2);
		CPPUNIT_ASSERT(v == vec2(1, 2));
	}

	void testComponentMult()
	{
		vec2 v1(2, 3);
		vec2 v2(-4, 5);
		vec2 v = v1.ComponentMult(v2);
		CPPUNIT_ASSERT(v == vec2(-8, 15));
	}

	void testDot()
	{
		vec2 v1(2, 3);
		vec2 v2(-4, 5);
		float v = v1.Dot(v2);
		CPPUNIT_ASSERT(v == 7);
	}

	void testToString()
	{
		vec2 v(2, 3);
		String s = v.ToString();
		CPPUNIT_ASSERT(s == "(2; 3)");
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(Vector2Test);



