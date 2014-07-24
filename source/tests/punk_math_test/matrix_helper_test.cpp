#include <math/forward.h>
#include <math/matrix.h>
#include "matrix_helper_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixHelperTest);

using namespace Punk::Engine::Math;

void MatrixHelperTest::testCreateTargetCameraMatrix() {

}

void MatrixHelperTest::testCreateFreeCameraMatrix() {

}

void MatrixHelperTest::testCreatePerspectiveProjection() {

}

void MatrixHelperTest::testCreateOrthographicProjection() {
    float l = 0;
    float r = 1;
    float t = 1;
    float b = 0;
    float n = 0;
    float f = 1;
    mat4 test {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, -2, 0, -1, -1, -1, 1};
    mat4 m = mat4::CreateOrthographicProjection(l, r, b, t, n, f);
    CPPUNIT_ASSERT(test == m);
}

void MatrixHelperTest::testCreateOrthographicProjection2() {

}

void MatrixHelperTest::testCreateTextureBiasMatrix() {
    mat4 test {0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.5, 0, 0.5, 0.5, 0.5, 1};
    mat4 m = mat4::CreateTextureBiasMatrix();
    CPPUNIT_ASSERT(test == m);
}

void MatrixHelperTest::testCreateCropMatrix() {

}

void MatrixHelperTest::testCreateLightProjectionMatrix() {

}

void MatrixHelperTest::testCreateFromQuaternion() {
    quat q{1,-1, 3, 2};
    mat4 test{-11.0f/15.0f, -2.0f/15.0f, -2.0f/3.0f, 0,
              -2.0f/3.0f, 1.0f/3.0f, 2.0f/3.0f, 0,
              2.0f/15.0f, 14.0f/15.0f, -1.0f/3.0f, 0,
             0, 0, 0, 1};
    q.Normalize();
    mat4 m = mat4::CreateFromQuaternion(q);
    CPPUNIT_ASSERT(m.IsEqual(test));
}

void MatrixHelperTest::testCreateFromPoistionAndDirection() {

}

void MatrixHelperTest::testCreatePerspectiveProjectionInfinity() {
    float n = 1;
    float r = 1;
    float l = 0;
    float t = 1;
    float b = 0;
    mat4 test{2, 0, 0, 0, 0, 2, 0, 0, 1, 1, -1, -1, 0, 0, -2, 0};
    mat4 m = mat4::CreatePerspectiveProjectionInfinity(l, r, t, b, n);
    CPPUNIT_ASSERT(test == m);
}

void MatrixHelperTest::testCreateIdentity() {

}

void MatrixHelperTest::testCreateScaling() {

}

void MatrixHelperTest::testCreateTranslate() {

}

void MatrixHelperTest::testCreateZRotation() {

}

void MatrixHelperTest::testCreateXRotation() {

}

void MatrixHelperTest::testCreateYRotation() {

}

void MatrixHelperTest::testCreateRotation() {

}

void MatrixHelperTest::testCreateReflectZ() {

}

void MatrixHelperTest::testCreateReflectX() {

}

void MatrixHelperTest::testCreateReflectY() {

}

void MatrixHelperTest::testCreateFromYawPitchRoll() {

}
