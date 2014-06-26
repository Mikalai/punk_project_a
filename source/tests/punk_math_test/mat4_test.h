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
};

#endif // TEST_MAT4_H
