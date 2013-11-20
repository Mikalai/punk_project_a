#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "string/string.h"
#include "vec4_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Vector4Test);

using namespace Punk::Engine::Core;
using namespace Punk::Engine::Math;

void Vector4Test::testVector4() {
    vec4 v1(1, 2, 3, 4);
    CPPUNIT_ASSERT(v1[0] == 1);
    CPPUNIT_ASSERT(v1[1] == 2);
    CPPUNIT_ASSERT(v1[2] == 3);
    CPPUNIT_ASSERT(v1[3] == 4);
    vec4 v2(1);
    CPPUNIT_ASSERT(v2[0] == 1);
    CPPUNIT_ASSERT(v2[1] == 1);
    CPPUNIT_ASSERT(v2[2] == 1);
    CPPUNIT_ASSERT(v2[3] == 1);
    vec4 v3(v1,v2);
    CPPUNIT_ASSERT(v3[0] == 0);
    CPPUNIT_ASSERT(v3[1] == 1);
    CPPUNIT_ASSERT(v3[2] == 2);
    CPPUNIT_ASSERT(v3[3] == 3);
    vec3 v5(1, 2, 3);
    vec4 v4(v5, 5);
    CPPUNIT_ASSERT(v4[0] == 1);
    CPPUNIT_ASSERT(v4[1] == 2);
    CPPUNIT_ASSERT(v4[2] == 3);
    CPPUNIT_ASSERT(v4[3] == 5);
    vec4 v6;
    CPPUNIT_ASSERT(v6[0] == 0);
    CPPUNIT_ASSERT(v6[1] == 0);
    CPPUNIT_ASSERT(v6[2] == 0);
    CPPUNIT_ASSERT(v6[3] == 0);
}

void Vector4Test::testToHomogeneus() {
    vec4 v1{2, 4, 6, 2};
    vec3 v2 = v1.ToHomogeneus();
    CPPUNIT_ASSERT(v2 == vec3(1, 2, 3));
}

void Vector4Test::testIndex() {
    vec3 v5(1, 2, 3);
    vec4 v4(v5, 5);
    CPPUNIT_ASSERT(v4[0] == 1);
    CPPUNIT_ASSERT(v4[1] == 2);
    CPPUNIT_ASSERT(v4[2] == 3);
    CPPUNIT_ASSERT(v4[3] == 5);
}

void Vector4Test::testXYZW() {
    vec4 v1(1, 2, 3, 4);
    CPPUNIT_ASSERT(v1.X() == 1);
    CPPUNIT_ASSERT(v1.Y() == 2);
    CPPUNIT_ASSERT(v1.Z() == 3);
    CPPUNIT_ASSERT(v1.W() == 4);
    CPPUNIT_ASSERT(v1.XY() == vec2(1, 2));
    CPPUNIT_ASSERT(v1.XZ() == vec2(1, 3));
    CPPUNIT_ASSERT(v1.XW() == vec2(1, 4));
    CPPUNIT_ASSERT(v1.YX() == vec2(2, 1));
    CPPUNIT_ASSERT(v1.YZ() == vec2(2, 3));
    CPPUNIT_ASSERT(v1.YW() == vec2(2, 4));
    CPPUNIT_ASSERT(v1.ZX() == vec2(3, 1));
    CPPUNIT_ASSERT(v1.ZY() == vec2(3, 2));
    CPPUNIT_ASSERT(v1.ZW() == vec2(3, 4));
    CPPUNIT_ASSERT(v1.WX() == vec2(4, 1));
    CPPUNIT_ASSERT(v1.WY() == vec2(4, 2));
    CPPUNIT_ASSERT(v1.WZ() == vec2(4, 3));

    CPPUNIT_ASSERT(v1.XYZ() == vec3(1, 2, 3));
    CPPUNIT_ASSERT(v1.XYW() == vec3(1, 2, 4));
    CPPUNIT_ASSERT(v1.XZY() == vec3(1, 3, 2));
    CPPUNIT_ASSERT(v1.XZW() == vec3(1, 3, 4));
    CPPUNIT_ASSERT(v1.XWZ() == vec3(1, 4, 3));
    CPPUNIT_ASSERT(v1.XWY() == vec3(1, 4, 2));

    CPPUNIT_ASSERT(v1.YXZ() == vec3(2, 1, 3));
    CPPUNIT_ASSERT(v1.YXW() == vec3(2, 1, 4));
    CPPUNIT_ASSERT(v1.YZX() == vec3(2, 3, 1));
    CPPUNIT_ASSERT(v1.YZW() == vec3(2, 3, 4));
    CPPUNIT_ASSERT(v1.YWX() == vec3(2, 4, 1));
    CPPUNIT_ASSERT(v1.YWZ() == vec3(2, 4, 3));

    CPPUNIT_ASSERT(v1.ZXY() == vec3(3, 1, 2));
    CPPUNIT_ASSERT(v1.ZXW() == vec3(3, 1, 4));
    CPPUNIT_ASSERT(v1.ZYX() == vec3(3, 2, 1));
    CPPUNIT_ASSERT(v1.ZYW() == vec3(3, 2, 4));
    CPPUNIT_ASSERT(v1.ZWX() == vec3(3, 4, 1));
    CPPUNIT_ASSERT(v1.ZWY() == vec3(3, 4, 2));

    CPPUNIT_ASSERT(v1.WXY() == vec3(4, 1, 2));
    CPPUNIT_ASSERT(v1.WXZ() == vec3(4, 1, 3));
    CPPUNIT_ASSERT(v1.WYX() == vec3(4, 2, 1));
    CPPUNIT_ASSERT(v1.WYZ() == vec3(4, 2, 3));
    CPPUNIT_ASSERT(v1.WZX() == vec3(4, 3, 1));
    CPPUNIT_ASSERT(v1.WZY() == vec3(4, 3, 2));

    CPPUNIT_ASSERT(v1.XYZW() == vec4(1, 2, 3, 4));
    CPPUNIT_ASSERT(v1.XYWZ() == vec4(1, 2, 4, 3));
    CPPUNIT_ASSERT(v1.XZYW() == vec4(1, 3, 2, 4));
    CPPUNIT_ASSERT(v1.XZWY() == vec4(1, 3, 4, 3));
    CPPUNIT_ASSERT(v1.XWYZ() == vec4(1, 4, 2, 3));
    CPPUNIT_ASSERT(v1.XWZY() == vec4(1, 4, 3, 2));

    CPPUNIT_ASSERT(v1.YXZW() == vec4(2, 1, 3, 4));
    CPPUNIT_ASSERT(v1.YXWZ() == vec4(2, 1, 4, 3));
    CPPUNIT_ASSERT(v1.YZXW() == vec4(2, 3, 1, 4));
    CPPUNIT_ASSERT(v1.YZWX() == vec4(2, 3, 4, 1));
    CPPUNIT_ASSERT(v1.YWXZ() == vec4(2, 4, 1, 3));
    CPPUNIT_ASSERT(v1.YWZX() == vec4(2, 4, 3, 1));

    CPPUNIT_ASSERT(v1.ZXYW() == vec4(3, 1, 2, 4));
    CPPUNIT_ASSERT(v1.ZXWY() == vec4(3, 1, 4, 2));
    CPPUNIT_ASSERT(v1.ZYXW() == vec4(3, 2, 1, 4));
    CPPUNIT_ASSERT(v1.ZYWX() == vec4(3, 2, 4, 1));
    CPPUNIT_ASSERT(v1.ZWXY() == vec4(3, 4, 1, 2));
    CPPUNIT_ASSERT(v1.ZWYX() == vec4(3, 4, 2, 1));

    CPPUNIT_ASSERT(v1.WXYZ() == vec4(4, 1, 2, 3));
    CPPUNIT_ASSERT(v1.WXZY() == vec4(4, 1, 3, 2));
    CPPUNIT_ASSERT(v1.WYXZ() == vec4(4, 2, 1, 3));
    CPPUNIT_ASSERT(v1.WYZX() == vec4(4, 2, 3, 1));
    CPPUNIT_ASSERT(v1.WZXY() == vec4(4, 3, 1, 2));
    CPPUNIT_ASSERT(v1.WZYX() == vec4(4, 3, 2, 1));
}

void Vector4Test::testOperator() {
    vec4 v(1,2,3,4);
    v *= 2;
    CPPUNIT_ASSERT(v == vec4(2, 4, 6, 8));
    v /= 2;
    CPPUNIT_ASSERT(v == vec4(1, 2, 3, 4));
    v += vec4(2, 4, 6, 8);
    CPPUNIT_ASSERT(v == vec4(3, 6, 9, 12));
    v -= vec4(2, 4, 6, 8);
    CPPUNIT_ASSERT(v == vec4(1, 2, 3, 4));
}

void Vector4Test::testLength() {
    vec4 v(8,4,2,4);
    float l = v.Length();
    CPPUNIT_ASSERT(l == 10);
}

void Vector4Test::testNormalized() {
    vec4 v(5, 0, 0, 0);
    vec4 v1 = v.Normalized();
    CPPUNIT_ASSERT(v1 == vec4(1, 0, 0, 0));
    v.Normalize();
    CPPUNIT_ASSERT(v == vec4(1, 0, 0, 0));
}

void Vector4Test::testDot() {
    vec4 v1(2, 3, 4, 5);
    vec4 v2(6, 7, 8, 9);
    float v = v1.Dot(v2);
    CPPUNIT_ASSERT(v == 110);
}

void Vector4Test::testSet() {
    vec4 v;
    v.Set(1,2,3,4);
    CPPUNIT_ASSERT(v == vec4(1,2,3,4));
}

void Vector4Test::testComponentMul() {
    vec4 v1(2, 3, 4, 5);
    vec4 v2(6, 7, 8, 9);
    vec4 v = v1.ComponentMul(v2);
    CPPUNIT_ASSERT(v == vec4(12, 21, 32, 45));
}

void Vector4Test::testToString() {
    vec4 v(1, 2, 3, 4);
    String s = v.ToString();
    CPPUNIT_ASSERT(s == "(1; 2; 3; 4)");
}
