#ifndef MAT2_TEST_H
#define MAT2_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Matrix2x2Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Matrix2x2Test);
    CPPUNIT_TEST(testCreateIdentity);
    CPPUNIT_TEST(testCreateMirrorX);
    CPPUNIT_TEST(testCreateMirrorY);
    CPPUNIT_TEST(testCreateMirrorXY);
    CPPUNIT_TEST(testMatrix2x2);
    CPPUNIT_TEST(testIndex);
    CPPUNIT_TEST(testRowColumn);
    CPPUNIT_TEST(testDeterminant);
    CPPUNIT_TEST(testInverse);
    CPPUNIT_TEST(testSetColumn);
    CPPUNIT_TEST(testSetRow);
    CPPUNIT_TEST(testIdentity);
    CPPUNIT_TEST(testOperator);
    CPPUNIT_TEST_SUITE_END();
public:
    void testCreateIdentity();
    void testCreateMirrorX();
    void testCreateMirrorY();
    void testCreateMirrorXY();
    void testMatrix2x2();
    void testIndex();
    void testRowColumn();
    void testDeterminant();
    void testInverse();
    void testSetColumn();
    void testSetRow();
    void testIdentity();
    void testOperator();
};

#endif // MAT2_TEST_H
