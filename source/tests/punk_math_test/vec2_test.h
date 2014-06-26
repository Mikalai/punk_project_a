#ifndef VEC2_TEST_H
#define VEC2_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Vector2Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Vector2Test);
    CPPUNIT_TEST(testXYRG);
    CPPUNIT_TEST(testIndex);
    CPPUNIT_TEST(testVector2);
    CPPUNIT_TEST(testNormalize);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST(testSqrLength);
    CPPUNIT_TEST(testNegate);
    CPPUNIT_TEST(testSet);
    CPPUNIT_TEST(testComponentMult);
    CPPUNIT_TEST(testDot);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST_SUITE_END();
public:    
    void testXYRG();
    void testIndex();
    void testVector2();
    void testNormalize();
    void testLength();
    void testSqrLength();
    void testNegate();
    void testSet();
    void testComponentMult();
    void testDot();
    void testToString();
};

#endif // VEC2_TEST_H
