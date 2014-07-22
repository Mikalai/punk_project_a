#include "vec3_test.h"
#include "math/vec3.h"
#include "math/vec2.h"
#include "string/string.h"

using namespace Punk::Engine::Math;
using namespace Punk::Engine::Core;

void f() {
		{
			TupleData<float, 3, tagVector> d{ 1, 2, 3 };
			vec3 vv = d;
		}
	{
		TupleData<float, 2, tagVector> d{ 1, 2 };
		vec2 vv = d;
	}
	vec3 v{ 1, 2, 3 };

	{
		TupleOperations<float, 3, tagVector>& a = v;
	}

	{
		TupleOperationsBase<float, 3, tagVector>& a = v;
	}

	{
		TupleComponentAccessor<float, 3, tagVector>& a = v;
	}

	{
		TupleComponentAccessorBase<float, 3, tagVector>& a = v;
	}
	{
		TupleData<float, 3, tagVector>& a = v;
	}
}

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Vector3Test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Vector3Test);
	CPPUNIT_TEST(testVec3);
	CPPUNIT_TEST(testNull);
	CPPUNIT_TEST(testXYZ);
	CPPUNIT_TEST(testNegate);
	CPPUNIT_TEST(testLength);
	CPPUNIT_TEST(testNormalized);
	CPPUNIT_TEST(testCross);
	CPPUNIT_TEST(testChop);
	CPPUNIT_TEST(testComponentMult);
	CPPUNIT_TEST(testNullify);
	CPPUNIT_TEST(testOperations);
	CPPUNIT_TEST(testIndex);
	CPPUNIT_TEST(testSquareLength);
	CPPUNIT_TEST(testSet);
	CPPUNIT_TEST(testDot);
	CPPUNIT_TEST(testToString);
	CPPUNIT_TEST_SUITE_END();
public:
	void testVec3();
	void testNull();
	void testXYZ();
	void testNegate();
	void testLength();
	void testNormalized();
	void testCross();
	void testChop();
	void testComponentMult();
	void testNullify();
	void testOperations();
	void testIndex();
	void testSquareLength();
	void testSet();
	void testDot();
	void testToString();
};

CPPUNIT_TEST_SUITE_REGISTRATION(Vector3Test);


void Vector3Test::testVec3() {
    vec3 v1{};
    CPPUNIT_ASSERT(v1 == vec3(0.0f,0.0f,0.0f));
    vec3 v2(1, 2, 3);
    CPPUNIT_ASSERT(v2[0] == 1);
    CPPUNIT_ASSERT(v2[1] == 2);
    CPPUNIT_ASSERT(v2[2] == 3);
    vec3 v3{1, 2, 3, 4};
    CPPUNIT_ASSERT(v3[0] == 1);
    CPPUNIT_ASSERT(v3[1] == 2);
    CPPUNIT_ASSERT(v3[2] == 3);
    vec3 v4(v3);
    CPPUNIT_ASSERT(v4[0] == 1);
    CPPUNIT_ASSERT(v4[1] == 2);
    CPPUNIT_ASSERT(v4[2] == 3);
}

void Vector3Test::testNull() {
    vec3 v = vec3::Null();
    CPPUNIT_ASSERT(v[0] == 0);
    CPPUNIT_ASSERT(v[1] == 0);
    CPPUNIT_ASSERT(v[2] == 0);
}

void Vector3Test::testXYZ() {
    vec3 v(1,2,3);
    CPPUNIT_ASSERT(v.X() == 1);
    CPPUNIT_ASSERT(v.Y() == 2);
    CPPUNIT_ASSERT(v.Z() == 3);
    CPPUNIT_ASSERT(v.XY() == vec2(1, 2));
    CPPUNIT_ASSERT(v.YX() == vec2(2, 1));
    CPPUNIT_ASSERT(v.XZ() == vec2(1, 3));
    CPPUNIT_ASSERT(v.ZX() == vec2(3, 1));
    CPPUNIT_ASSERT(v.YZ() == vec2(2, 3));
    CPPUNIT_ASSERT(v.ZY() == vec2(3, 2));
    CPPUNIT_ASSERT(v.XYZ() == vec3(1, 2, 3));
    CPPUNIT_ASSERT(v.XZY() == vec3(1, 3, 2));
    CPPUNIT_ASSERT(v.YXZ() == vec3(2, 1, 3));
    CPPUNIT_ASSERT(v.YZX() == vec3(2, 3, 1));
    CPPUNIT_ASSERT(v.ZXY() == vec3(3, 1, 2));
    CPPUNIT_ASSERT(v.ZYX() == vec3(3, 2, 1));
}

void Vector3Test::testNegate() {
    vec3 v1(1, 2, 3);
    vec3 v2 = v1.Negated();
    CPPUNIT_ASSERT(v2 == vec3(-1, -2, -3));
    vec3 v3 = -v1;
    CPPUNIT_ASSERT(v3 == vec3(-1, -2, -3));
    v1.Negate();
    CPPUNIT_ASSERT(v1 == vec3(-1, -2, -3));
}

void Vector3Test::testLength() {
    vec3 v1(2,3,6);
    float l = v1.Length();
    CPPUNIT_ASSERT(l == 7.0f);
}

void Vector3Test::testNormalized() {
    vec3 v1(4, 0, 0);
    vec3 v2 = v1.Normalized();
    CPPUNIT_ASSERT(v2 == vec3(1, 0, 0));
    v1.Normalize();
    CPPUNIT_ASSERT(v1 == vec3(1, 0, 0));
}

void Vector3Test::testCross() {
    vec3 v1(1, 2, 3);
    vec3 v2(6, 5, 9);
    vec3 v = v1.Cross(v2);
    CPPUNIT_ASSERT(v == vec3(3, 9, -7));
}

void Vector3Test::testChop() {
    vec3 v(1e-7, 1e-6, 1e-9);
    CPPUNIT_ASSERT(v != vec3(0,0,0));
    v.Chop(1e-5);
    CPPUNIT_ASSERT(v == vec3(0,0,0));
}

void Vector3Test::testComponentMult() {
    Tuple<float, 3, tagVector> v1(2, 4, 6);
    Tuple<float, 3, tagVector> v2(7, 5, 3);
    Tuple<float, 3, tagVector> v = v1.ComponentMult(v2);
    CPPUNIT_ASSERT(v == vec3(14, 20, 18));
}

void Vector3Test::testNullify() {
    vec3 v(1, 2, 3);
    CPPUNIT_ASSERT(v != vec3(0,0,0));
    v.Nullify();
    CPPUNIT_ASSERT(v == vec3(0,0,0));
}

void Vector3Test::testOperations() {
    vec3 v(2, 3, 4);
    v += {1, 2, 3};
    CPPUNIT_ASSERT(v == vec3(3, 5, 7));
    v -= {1, 2, 1};
    CPPUNIT_ASSERT(v == vec3(2, 3, 6));
    v *= 2;
    CPPUNIT_ASSERT(v == vec3(4, 6, 12));
    v /= 2;
    CPPUNIT_ASSERT(v == vec3(2, 3, 6));
}

void Vector3Test::testIndex() {
    vec3 v(1, 2, 3);
    CPPUNIT_ASSERT(v[0] == 1);
    CPPUNIT_ASSERT(v[1] == 2);
    CPPUNIT_ASSERT(v[2] == 3);
}

void Vector3Test::testSquareLength() {
    vec3 v(2, 3, 4);
    float f = v.SquareLength();
    CPPUNIT_ASSERT(f == 29);
}

void Vector3Test::testSet() {
    vec3 v;
    v.Set(1, 2, 3);
    CPPUNIT_ASSERT(v == vec3(1, 2, 3));
}

void Vector3Test::testDot() {
    vec3 v1(2, 3, 4);
    vec3 v2(7, 6, 5);
    float r = v1.Dot(v2);
    CPPUNIT_ASSERT(r == (14 + 18 +20));
}

void Vector3Test::testToString()
{
    vec3 v1(1, 2, 3);
    String s = v1.ToString();
    CPPUNIT_ASSERT(s == "(1; 2; 3)");
}
