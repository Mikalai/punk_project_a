#include "string/string.h"
#include "string/string_list.h"
#include "string_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(StringTest);

using namespace Punk::Engine::Core;

void StringTest::testString() {
    String s1;
    CPPUNIT_ASSERT(s1 == "");
    CPPUNIT_ASSERT(s1 == L"");

    String s2("Hello world");
    CPPUNIT_ASSERT(s2 == "Hello world");
    CPPUNIT_ASSERT(s2 == L"Hello world");

    String s3(L"Hello world");
    CPPUNIT_ASSERT(s3 == "Hello world");
    CPPUNIT_ASSERT(s3 == L"Hello world");

    String s4("Hello world", 5);
    CPPUNIT_ASSERT(s4 == "Hello");
    CPPUNIT_ASSERT(s4 == L"Hello");

    String s5(L"Hello world", 5);
    CPPUNIT_ASSERT(s5 == "Hello");
    CPPUNIT_ASSERT(s5 == L"Hello");

    String s6('*', 5);
    CPPUNIT_ASSERT(s6 == "*****");
    CPPUNIT_ASSERT(s6 == L"*****");

    String s7(L'*', 5);
    CPPUNIT_ASSERT(s7 == "*****");
    CPPUNIT_ASSERT(s7 == L"*****");

    s1 = "Motorhead";
    CPPUNIT_ASSERT(s1 == "Motorhead");
    CPPUNIT_ASSERT(s1 == L"Motorhead");

    s1 = L"Motorhead";
    CPPUNIT_ASSERT(s1 == "Motorhead");
    CPPUNIT_ASSERT(s1 == L"Motorhead");

    s1 = s2;
    CPPUNIT_ASSERT(s1 == s2);

    s1 = s1;
}

void StringTest::testEqual() {
    String s1("Hello world");
    String s2(L"Hello world");
    String s3("This is not a love song");

    CPPUNIT_ASSERT(s1 == s2);
    CPPUNIT_ASSERT(s1 != s3);
    CPPUNIT_ASSERT(s1 == "Hello world");
    CPPUNIT_ASSERT(s1 != "Hi, Jack!!!");
}

void StringTest::testAdd() {
    String s1("Star");
    s1 += " Trek";
    CPPUNIT_ASSERT(s1 == "Star Trek");
}

void StringTest::testIndexer() {
    String s1("Hello world");
    CPPUNIT_ASSERT(s1[0] == 'H');
    CPPUNIT_ASSERT(s1[0] != 'h');	
}

void StringTest::testLength() {
    String s1("Hello world");
    CPPUNIT_ASSERT(s1.Length() == 11);
}

void StringTest::testSize() {
    String s1("Hello world");
    CPPUNIT_ASSERT(s1.Size() == s1.Length()*sizeof(wchar_t));
}

void StringTest::testErase() {
    String s1("Hello world");
    s1.Erase(0, 6);
    CPPUNIT_ASSERT(s1 == "world");
    s1.Erase(2, 2);
    CPPUNIT_ASSERT(s1 == "wod");
}

void StringTest::testInsert() {
    String s1("Hd");
    s1.Insert('u', 1);
    CPPUNIT_ASSERT(s1 == "Hud");
}

void StringTest::testReplace() {
    String s1("I'm the very happy dude");
    s1 = s1.Replace("e", "ooo");
    CPPUNIT_ASSERT(s1 == "I'm thooo vooory happy dudooo");
}

void StringTest::testSubString() {
    String s1("Hello world");
    s1 = s1.SubString(3, 5);
    CPPUNIT_ASSERT(s1 == "lo wo");
}

void StringTest::testTrim() {
    String s1("    .....This .is. good....   ");
    s1 = s1.Trim(" .");
    CPPUNIT_ASSERT(s1 == "This .is. good");
}

void StringTest::testSplit() {
    String s("I'm the man");
    StringList list = s.Split(" ");
    StringList test {"I'm", "the", "man" };
    CPPUNIT_ASSERT(list == test);
}

void StringTest::testEndWith() {
    String s("I'm the dude");
    CPPUNIT_ASSERT(s.EndWith("the dude"));
}

void StringTest::testStartWith() {
    String s("I'm the dude");
    CPPUNIT_ASSERT(s.EndWith("I'm the"));
}

void StringTest::testData() {

}

void StringTest::testToAscii() {

}

void StringTest::testToUtf8() {

}

void StringTest::testToInt32() {

}

void StringTest::testToInt32FromHex() {

}

void StringTest::testToFloat() {

}

void StringTest::testToDouble() {

}

void StringTest::testToLower() {
    String s1("Hello world");
    s1 = s1.ToLower();
    CPPUNIT_ASSERT(s1 == "hello world");
}

void StringTest::testToUpper() {
    String s1("Hello world");
    s1 = s1.ToUpper();
    CPPUNIT_ASSERT(s1 == "HELLO WORLD");
}

void StringTest::testArg() {
    String s("{0} {1} {2} {3} {4} {5} {6} {7} {8} {9} {10} {11} {12}");
    s.arg(std::int8_t(3))
            .arg(std::uint8_t(4))
            .arg(std::int16_t(500))
            .arg(std::uint16_t(600))
            .arg(std::int32_t(100000))
            .arg(std::uint32_t(101000))
            .arg(std::uint64_t(1000000000000))
            .arg(std::int64_t(1001000000000))
            .arg(1.5f)
            .arg(2.5)
            .arg(String("Hello"))
            .arg(true)
            .arg("world");

    CPPUNIT_ASSERT(s == "3 4 500 600 100000 101000 1000000000000 1001000000000 1.5 2.5 Hello 1 world");}

void StringTest::testConvert() {

}

