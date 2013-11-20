#include "math/mat2.h"
#include "math/vec2.h"
#include "mat2_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Matrix2x2Test);

using namespace Punk::Engine::Math;
using namespace Punk::Engine::Core;

void Matrix2x2Test::testCreateIdentity() {
    mat2 m = mat2::CreateIdentity();
    CPPUNIT_ASSERT(m[0] == 1);
    CPPUNIT_ASSERT(m[1] == 0);
    CPPUNIT_ASSERT(m[2] == 0);
    CPPUNIT_ASSERT(m[3] == 1);
}

void Matrix2x2Test::testCreateMirrorX() {
    mat2 test{1, 0, 0, -1};
    mat2 m = mat2::CreateMirrorX();
    CPPUNIT_ASSERT(m == test);
}

void Matrix2x2Test::testCreateMirrorY() {
    mat2 test{-1, 0, 0, 1};
    mat2 m = mat2::CreateMirrorY();
    CPPUNIT_ASSERT(m == test);
}

void Matrix2x2Test::testCreateMirrorXY() {
    mat2 test{-1, 0, 0, -1};
    mat2 m = mat2::CreateMirrorXY();
    CPPUNIT_ASSERT(m == test);
}

void Matrix2x2Test::testMatrix2x2() {
    mat2 i{1.0f, 0.0f, 0.0f, 1.0f};
    mat2 m1;
    CPPUNIT_ASSERT(m1 == i);
    mat2 m2{1, 2, 3, 4};
    CPPUNIT_ASSERT(m2[0] == 1);
    CPPUNIT_ASSERT(m2[1] == 2);
    CPPUNIT_ASSERT(m2[2] == 3);
    CPPUNIT_ASSERT(m2[3] == 4);
}

void Matrix2x2Test::testIndex() {
    mat2 m2{1, 2, 3, 4};
    CPPUNIT_ASSERT(m2[0] == 1);
    CPPUNIT_ASSERT(m2[1] == 2);
    CPPUNIT_ASSERT(m2[2] == 3);
    CPPUNIT_ASSERT(m2[3] == 4);
}

void Matrix2x2Test::testRowColumn() {
    mat2 m2{1, 2, 3, 4};
    vec2 row0 = m2.Row(0);
    CPPUNIT_ASSERT(row0 = vec2(1, 3));
    vec2 row1 = m2.Row(1);
    CPPUNIT_ASSERT(row1 == vec2(2, 4));
}

void Matrix2x2Test::testDeterminant() {
    mat2 m{1, 2, 3, 4};
    float d = m.Determinant();
    CPPUNIT_ASSERT(d == -2);
    mat2 m2{2, 4, 4, 8};
    d = m2.Determinant();
    CPPUNIT_ASSERT(d == 0);
}

void Matrix2x2Test::testInverse() {
    mat2 test{-2, 1, 1.5f, -0.5f};
    mat2 m1{1, 2, 3, 4};
    mat2 m2 = m1.Inversed();
    CPPUNIT_ASSERT(m2 == test);
    m1.Inverse();
    CPPUNIT_ASSERT(m1 == test);
}

void Matrix2x2Test::testSetColumn() {
    mat2 test{1, 2, 0, 1};
    mat2 m;
    m.SetColumn(0, {1, 2});
    CPPUNIT_ASSERT(m == test);
}

void Matrix2x2Test::testSetRow() {
    mat2 test{1, 0, 2, 1};
    mat2 m;
    m.SetRow(0, {1, 2});
    CPPUNIT_ASSERT(m == test);
}

void Matrix2x2Test::testIdentity() {
    mat2 m{1,2,3,4};
    CPPUNIT_ASSERT(m != mat2::CreateIdentity());
    m.Identity();
    CPPUNIT_ASSERT(m == mat2::CreateIdentity());
}

void Matrix2x2Test::testOperator() {
    mat2 m1{1,2,3,4};
    mat2 m2{5,6,7,8};
    mat2 m = m1 + m2;
    CPPUNIT_ASSERT(m == mat2(6, 8, 10, 12));
    m = m1 - m2;
    CPPUNIT_ASSERT(m == mat2(-4, -4, -4, -4));
    m = m1 * m2;
    CPPUNIT_ASSERT(m == mat2(23, 34, 31, 46));
}
