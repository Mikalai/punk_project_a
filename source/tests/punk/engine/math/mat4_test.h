#ifndef TEST_MAT4_H
#define TEST_MAT4_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Matrix4x4Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Matrix4x4Test);
    CPPUNIT_TEST(testMatrix4x4);
    CPPUNIT_TEST(testInversed);
    CPPUNIT_TEST(testRotationPart);
    CPPUNIT_TEST(testTranslationPart);
    CPPUNIT_TEST(testIndex);
    CPPUNIT_TEST(testSetColumn);
    CPPUNIT_TEST(testSetRow);
    CPPUNIT_TEST(testGetRow);
    CPPUNIT_TEST(testGetColumn);
    CPPUNIT_TEST(testIdentity);
    CPPUNIT_TEST(testTransposed);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testOperator);
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
    void testMatrix4x4();
    void testInversed();
    void testRotationPart();
    void testTranslationPart();
    void testIndex();
    void testSetColumn();
    void testSetRow();
    void testGetRow();
    void testGetColumn();
    void testIdentity();
    void testTransposed();
    void testToString();
    void testOperator();
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

#endif // TEST_MAT4_H
