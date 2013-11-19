#ifndef STRING_TEST_H
#define STRING_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class StringTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(StringTest);
    CPPUNIT_TEST(testString);
    CPPUNIT_TEST(testEqual);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testIndexer);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testErase);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testReplace);
    CPPUNIT_TEST(testSubString);
    CPPUNIT_TEST(testTrim);
    CPPUNIT_TEST(testSplit);
    CPPUNIT_TEST(testEndWith);
    CPPUNIT_TEST(testStartWith);
    CPPUNIT_TEST(testData);
    CPPUNIT_TEST(testToAscii);
    CPPUNIT_TEST(testToUtf8);
    CPPUNIT_TEST(testToInt32);
    CPPUNIT_TEST(testToInt32FromHex);
    CPPUNIT_TEST(testToFloat);
    CPPUNIT_TEST(testToDouble);
    CPPUNIT_TEST(testToLower);
    CPPUNIT_TEST(testToUpper);
    CPPUNIT_TEST(testArg);
    CPPUNIT_TEST(testConvert);
    CPPUNIT_TEST_SUITE_END();

public:
    void testString();
    void testEqual();
    void testAdd();
    void testIndexer();
    void testLength();
    void testSize();
    void testErase();
    void testInsert();
    void testReplace();
    void testSubString();
    void testTrim();
    void testSplit();
    void testEndWith();
    void testStartWith();
    void testData();
    void testToAscii();
    void testToUtf8();
    void testToInt32();
    void testToInt32FromHex();
    void testToFloat();
    void testToDouble();
    void testToLower();
    void testToUpper();
    void testArg();
    void testConvert();
};

#endif // STRING_TEST_H
