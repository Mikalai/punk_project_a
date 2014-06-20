#ifndef VEC3_TEST_H
#define VEC3_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Vector3Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Vector3Test);
    CPPUNIT_TEST(testVec3);
    CPPUNIT_TEST(testNull);
    CPPUNIT_TEST(testXYZ);
    CPPUNIT_TEST(testNegate);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST(testNormalized);
    CPPUNIT_TEST(testCross);
    CPPUNIT_TEST(testChop);
    CPPUNIT_TEST(testComponentMult);
    CPPUNIT_TEST(testNullify);
    CPPUNIT_TEST(testOperations);
    CPPUNIT_TEST(testIndex);
    CPPUNIT_TEST(testSquareLength);
    CPPUNIT_TEST(testSet);
    CPPUNIT_TEST(testDot);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST_SUITE_END();
public:
    void testVec3();
    void testNull();
    void testXYZ();
    void testNegate();
    void testLength();
    void testNormalized();
    void testCross();
    void testChop();
    void testComponentMult();
    void testNullify();
    void testOperations();
    void testIndex();
    void testSquareLength();
    void testSet();
    void testDot();
    void testToString();
};

#endif // VEC3_TEST_H
