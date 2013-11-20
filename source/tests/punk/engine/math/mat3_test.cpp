#include "math/mat3.h"
#include "math/vec3.h"
#include "string/string.h"
#include "mat3_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Matrix3x3Test);

using namespace Punk::Engine::Core;
using namespace Punk::Engine::Math;

void Matrix3x3Test::testMatrix3x3() {
    mat3 m1;
    CPPUNIT_ASSERT(m1 == mat3::CreateIdentity());
    mat3 m2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 8; ++i)
    {
        CPPUNIT_ASSERT(m2[i] == i+1);
    }
    mat3 m3{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    for (int i = 0; i < 8; ++i)
    {
        CPPUNIT_ASSERT(m3[i] == i+1);
    }
    vec3 v1{{1, 4, 7}};
    vec3 v2{{2, 5, 8}};
    vec3 v3{{3, 6, 9}};
    mat3 m4(v1, v2, v3);
    for (int i = 0; i < 8; ++i)
    {
        CPPUNIT_ASSERT(m3[i] == i+1);
    }
}

void Matrix3x3Test::testIndex() {

}

void Matrix3x3Test::testOperator() {

}

void Matrix3x3Test::testDeterminant() {

}

void Matrix3x3Test::testSwapRows() {

}

void Matrix3x3Test::testChop() {

}

void Matrix3x3Test::testInverse() {

}

void Matrix3x3Test::testSetColumn() {

}

void Matrix3x3Test::testSetRow() {

}

void Matrix3x3Test::testIdentity() {

}

void Matrix3x3Test::testZerofy() {

}

void Matrix3x3Test::testTranslationPart() {

}

void Matrix3x3Test::testRotationPart() {

}

void Matrix3x3Test::testToString() {

}

void Matrix3x3Test::testTranspose() {

}

void Matrix3x3Test::testIsEqual() {

}

void Matrix3x3Test::testNull() {

}

void Matrix3x3Test::testCreate2DTranslate() {

}

void Matrix3x3Test::testCreate2DRotate() {

}

void Matrix3x3Test::testCreateFreeForm2DRotate() {

}

void Matrix3x3Test::testCreate2DScale() {

}

void Matrix3x3Test::testCreateIdentity() {

}

void Matrix3x3Test::testCreate2DFreeFormScale() {

}

void Matrix3x3Test::testCreate2DReflectionX() {

}

void Matrix3x3Test::testCreate2DOriginReflection() {

}

void Matrix3x3Test::testCreateFromQuaternion() {

}
