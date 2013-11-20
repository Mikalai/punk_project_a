#include "math/mat4.h"
#include "math/mat3.h"
#include "math/vec4.h"
#include "math/vec3.h"
#include "mat4_test.h"
#include "string/string.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Matrix4x4Test);

using namespace Punk::Engine::Core;
using namespace Punk::Engine::Math;

void Matrix4x4Test::testMatrix4x4() {

}

void Matrix4x4Test::testInversed() {

}

void Matrix4x4Test::testRotationPart() {

}

void Matrix4x4Test::testTranslationPart() {

}

void Matrix4x4Test::testIndex() {

}

void Matrix4x4Test::testSetColumn() {

}

void Matrix4x4Test::testSetRow() {

}

void Matrix4x4Test::testGetRow() {

}

void Matrix4x4Test::testGetColumn() {

}

void Matrix4x4Test::testIdentity() {

}

void Matrix4x4Test::testTransposed() {

}

void Matrix4x4Test::testToString() {

}

void Matrix4x4Test::testOperator() {

}

void Matrix4x4Test::testCreateTargetCameraMatrix() {

}

void Matrix4x4Test::testCreateFreeCameraMatrix() {

}

void Matrix4x4Test::testCreatePerspectiveProjection() {

}

void Matrix4x4Test::testCreateOrthographicProjection() {

}

void Matrix4x4Test::testCreateOrthographicProjection2() {

}

void Matrix4x4Test::testCreateTextureBiasMatrix() {

}

void Matrix4x4Test::testCreateCropMatrix() {

}

void Matrix4x4Test::testCreateLightProjectionMatrix() {

}

void Matrix4x4Test::testCreateFromQuaternion() {

}

void Matrix4x4Test::testCreateFromPoistionAndDirection() {

}

void Matrix4x4Test::testCreatePerspectiveProjectionInfinity() {
    float n = 1;
    float r = 1;
    float l = 0;
    float t = 1;
    float b = 0;
    mat4 test{2, 0, 0, 0, 0, 2, 0, 0, 1, 1, -1, -1, 0, 0, -2, 0};
    mat4 m = mat4::CreatePerspectiveProjectionInfinity(l, r, t, b, n);
    CPPUNIT_ASSERT(test == m);
}

void Matrix4x4Test::testCreateIdentity() {

}

void Matrix4x4Test::testCreateScaling() {

}

void Matrix4x4Test::testCreateTranslate() {

}

void Matrix4x4Test::testCreateZRotation() {

}

void Matrix4x4Test::testCreateXRotation() {

}

void Matrix4x4Test::testCreateYRotation() {

}

void Matrix4x4Test::testCreateRotation() {

}

void Matrix4x4Test::testCreateReflectZ() {

}

void Matrix4x4Test::testCreateReflectX() {

}

void Matrix4x4Test::testCreateReflectY() {

}

void Matrix4x4Test::testCreateFromYawPitchRoll() {

}
