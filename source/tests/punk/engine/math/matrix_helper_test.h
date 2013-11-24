#ifndef MATRIX_HELPER_TEST_H
#define MATRIX_HELPER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class MatrixHelperTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(MatrixHelperTest);
    CPPUNIT_TEST(testCreateTargetCameraMatrix);
    CPPUNIT_TEST(testCreateFreeCameraMatrix);
    CPPUNIT_TEST(testCreatePerspectiveProjection);
    CPPUNIT_TEST(testCreateOrthographicProjection);
    CPPUNIT_TEST(testCreateOrthographicProjection2);
    CPPUNIT_TEST(testCreateTextureBiasMatrix);
    CPPUNIT_TEST(testCreateCropMatrix);
    CPPUNIT_TEST(testCreateLightProjectionMatrix);
    CPPUNIT_TEST(testCreateFromQuaternion);
    CPPUNIT_TEST(testCreateFromPoistionAndDirection);
    CPPUNIT_TEST(testCreatePerspectiveProjectionInfinity);
    CPPUNIT_TEST(testCreateIdentity);
    CPPUNIT_TEST(testCreateScaling);
    CPPUNIT_TEST(testCreateTranslate);
    CPPUNIT_TEST(testCreateZRotation);
    CPPUNIT_TEST(testCreateXRotation);
    CPPUNIT_TEST(testCreateYRotation);
    CPPUNIT_TEST(testCreateRotation);
    CPPUNIT_TEST(testCreateReflectZ);
    CPPUNIT_TEST(testCreateReflectX);
    CPPUNIT_TEST(testCreateReflectY);
    CPPUNIT_TEST(testCreateFromYawPitchRoll);
    CPPUNIT_TEST_SUITE_END();
public:
    void testCreateTargetCameraMatrix();
    void testCreateFreeCameraMatrix();
    void testCreatePerspectiveProjection();
    void testCreateOrthographicProjection();
    void testCreateOrthographicProjection2();
    void testCreateTextureBiasMatrix();
    void testCreateCropMatrix();
    void testCreateLightProjectionMatrix();
    void testCreateFromQuaternion();
    void testCreateFromPoistionAndDirection();
    void testCreatePerspectiveProjectionInfinity();
    void testCreateIdentity();
    void testCreateScaling();
    void testCreateTranslate();
    void testCreateZRotation();
    void testCreateXRotation();
    void testCreateYRotation();
    void testCreateRotation();
    void testCreateReflectZ();
    void testCreateReflectX();
    void testCreateReflectY();
    void testCreateFromYawPitchRoll();
};

#endif // MATRIX_HELPER_TEST_H
