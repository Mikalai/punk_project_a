#ifndef STRING_LIST_TEST_H
#define STRING_LIST_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class StringListTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(StringListTest);
    CPPUNIT_TEST(testStringList);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testPush);
    CPPUNIT_TEST(testPop);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testEqual);
    CPPUNIT_TEST_SUITE_END();

public:
    void testStringList();
    void testSize();
    void testPush();
    void testPop();
    void testToString();
    void testEqual();
};

#endif // STRING_LIST_TEST_H
