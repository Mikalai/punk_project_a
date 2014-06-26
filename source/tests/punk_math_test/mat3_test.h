#ifndef MAT3_TEST_H
#define MAT3_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Matrix3x3Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Matrix3x3Test);
    CPPUNIT_TEST(testMatrix3x3);
    CPPUNIT_TEST(testIndex);
    CPPUNIT_TEST(testOperator);
    CPPUNIT_TEST(testDeterminant);
    CPPUNIT_TEST(testSwapRows);
    CPPUNIT_TEST(testChop);
    CPPUNIT_TEST(testInverse);
    CPPUNIT_TEST(testSetColumn);
    CPPUNIT_TEST(testSetRow);
    CPPUNIT_TEST(testIdentity);
    CPPUNIT_TEST(testZerofy);
    CPPUNIT_TEST(testTranslationPart);
    CPPUNIT_TEST(testRotationPart);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testTranspose);
    CPPUNIT_TEST(testIsEqual);
    CPPUNIT_TEST(testNull);
    CPPUNIT_TEST(testCreate2DTranslate);
    CPPUNIT_TEST(testCreate2DRotate);
    CPPUNIT_TEST(testCreateFreeForm2DRotate);
    CPPUNIT_TEST(testCreate2DScale);
    CPPUNIT_TEST(testCreateIdentity);
    CPPUNIT_TEST(testCreate2DFreeFormScale);
    CPPUNIT_TEST(testCreate2DReflectionX);
    CPPUNIT_TEST(testCreate2DReflectionY);
    CPPUNIT_TEST(testCreate2DOriginReflection);
    CPPUNIT_TEST(testCreateFromQuaternion);
    CPPUNIT_TEST_SUITE_END();
public:
    void testMatrix3x3();
    void testIndex();
    void testOperator();
    void testDeterminant();
    void testSwapRows();
    void testChop();
    void testInverse();
    void testSetColumn();
    void testSetRow();
    void testIdentity();
    void testZerofy();
    void testTranslationPart();
    void testRotationPart();
    void testToString();
    void testTranspose();
    void testIsEqual();
    void testNull();
    void testCreate2DTranslate();
    void testCreate2DRotate();
    void testCreateFreeForm2DRotate();
    void testCreate2DScale();
    void testCreateIdentity();
    void testCreate2DFreeFormScale();
    void testCreate2DReflectionX();
    void testCreate2DReflectionY();
    void testCreate2DOriginReflection();
    void testCreateFromQuaternion();
};

#endif // MAT3_TEST_H
