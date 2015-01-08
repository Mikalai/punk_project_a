#include "string/string.h"
#include "string/string_list.h"

using namespace Punk::Engine::Core;

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


CPPUNIT_TEST_SUITE_REGISTRATION(StringListTest);

void StringListTest::testStringList()
{
    StringList list1;
    CPPUNIT_ASSERT(list1.Size() == 0);
    StringList list2{"Hello", "world"};
    CPPUNIT_ASSERT(list2[0] == "Hello");
    CPPUNIT_ASSERT(list2[1] == "world");
}

void StringListTest::testSize()
{
    StringList list1{"Hello", "World"};
    CPPUNIT_ASSERT(list1.Size() == 2);
    list1.Push("Hello");
    CPPUNIT_ASSERT(list1.Size() == 3);
    list1.Pop();
    CPPUNIT_ASSERT(list1.Size() == 2);
}

void StringListTest::testPush()
{
    StringList list1{"Hello", "World"};
    CPPUNIT_ASSERT(list1.Size() == 2);
    list1.Push("Hello");
    CPPUNIT_ASSERT(list1.Size() == 3);
    list1.Pop();
    CPPUNIT_ASSERT(list1.Size() == 2);
}

void StringListTest::testPop()
{
    StringList list1{"Hello", "World"};
    CPPUNIT_ASSERT(list1.Size() == 2);
    list1.Push("Hello");
    CPPUNIT_ASSERT(list1.Size() == 3);
    list1.Pop();
    CPPUNIT_ASSERT(list1.Size() == 2);
}

void StringListTest::testToString()
{
    StringList list1{"Hello", " ", "world"};
    String s = list1.ToString("");
    CPPUNIT_ASSERT(s == "Hello world");
}

void StringListTest::testEqual()
{
    StringList list1{"Hello", "World"};
    StringList list2 = list1;
    CPPUNIT_ASSERT(list1 == list2);
}
