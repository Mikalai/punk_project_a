#include "vec2_test.h"
#include "math/vec2.h"
#include "string/string.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Vector2Test);

using namespace Punk::Engine::Math;
using namespace Punk::Engine::Core;

void Vector2Test::testXYRG() {
    vec2 v{1, 2};
    CPPUNIT_ASSERT(v.X() == 1);
    CPPUNIT_ASSERT(v.Y() == 2);
    CPPUNIT_ASSERT(v.XY() == vec2(1, 2));
    CPPUNIT_ASSERT(v.YX() == vec2(2, 1));
}

void Vector2Test::testIndex()
{
    vec2 v{1, 2};
    CPPUNIT_ASSERT(v[0] == 1);
    CPPUNIT_ASSERT(v[1] == 2);
}

void Vector2Test::testVector2()
{
    vec2 v1{1, 2};
    vec2 v2(1, 2);
    CPPUNIT_ASSERT(v1 == v2);
    vec2 v3(v1);
    CPPUNIT_ASSERT(v3 == v1);
    v1 = v2;
    CPPUNIT_ASSERT(v1 == v2);
}

void Vector2Test::testNormalize()
{
    vec2 v{5, 0};
    vec2 v2 = v.Normalized();
    CPPUNIT_ASSERT(v2 == vec2(1, 0));
    v.Normalize();
    CPPUNIT_ASSERT(v == vec2(1, 0));
}

void Vector2Test::testLength()
{
    vec2 v{3, 4};
    float l = v.Length();
    CPPUNIT_ASSERT(l == 5);
}

void Vector2Test::testSqrLength()
{
    vec2 v{3, 4};
    float l = v.Length();
    CPPUNIT_ASSERT(l == 5.0f);
}

void Vector2Test::testNegate()
{
    vec2 v1{3, 4};
    vec2 v2 = v1.Negated();
    CPPUNIT_ASSERT(v2 == vec2(-3, -4));
    vec2 v3 = -v1;
    CPPUNIT_ASSERT(v3 == vec2(-3, -4));
}

void Vector2Test::testSet()
{
    vec2 v;
    v.Set(1, 2);
    CPPUNIT_ASSERT(v == vec2(1, 2));
}

void Vector2Test::testComponentMult()
{
    vec2 v1(2, 3);
    vec2 v2(-4, 5);
    vec2 v = v1.ComponentMult(v2);
    CPPUNIT_ASSERT(v == vec2(-8, 15));
}

void Vector2Test::testDot()
{
    vec2 v1(2, 3);
    vec2 v2(-4, 5);
    float v = v1.Dot(v2);
    CPPUNIT_ASSERT(v == 7);
}

void Vector2Test::testToString()
{
    vec2 v(2, 3);
    String s = v.ToString();
    CPPUNIT_ASSERT(s == "(2; 3)");
}
