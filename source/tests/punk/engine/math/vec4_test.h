#ifndef VEC4_TEST_H
#define VEC4_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Vector4Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Vector4Test);
    CPPUNIT_TEST(testVector4);
    CPPUNIT_TEST(testToHomogeneus);
    CPPUNIT_TEST(testIndex);
    CPPUNIT_TEST(testXYZW);
    CPPUNIT_TEST(testOperator);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST(testNormalized);
    CPPUNIT_TEST(testDot);
    CPPUNIT_TEST(testSet);
    CPPUNIT_TEST(testComponentMul);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST_SUITE_END();

public:
    void testVector4();
    void testToHomogeneus();
    void testIndex();
    void testXYZW();
    void testOperator();
    void testLength();
    void testNormalized();
    void testDot();
    void testSet();
    void testComponentMul();
    void testToString();
};

#endif // VEC4_TEST_H
