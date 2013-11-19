#ifndef BUFFER_TEST_H
#define BUFFER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class BufferTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BufferTest);
    CPPUNIT_TEST(testSetPosition);
    CPPUNIT_TEST(testGetPosition);
    CPPUNIT_TEST(testGetSize);
    CPPUNIT_TEST(testSetSize);
    CPPUNIT_TEST(testData);
    CPPUNIT_TEST(testIsEnd);
    CPPUNIT_TEST(testReset);
    CPPUNIT_TEST(testReadSigned32);
    CPPUNIT_TEST(testReadUnsigned32);
    CPPUNIT_TEST(testReadSigned16);
    CPPUNIT_TEST(testReadUnsigned16);
    CPPUNIT_TEST(testReadSigned8);
    CPPUNIT_TEST(testReadUnsigned8);
    CPPUNIT_TEST(testReadSigned64);
    CPPUNIT_TEST(testReadUnsigned64);
    CPPUNIT_TEST(testReadString);
    CPPUNIT_TEST(testReadLine);
    CPPUNIT_TEST(testReadWord);
    CPPUNIT_TEST(testReadReal32);
    CPPUNIT_TEST(testReadReal64);
    CPPUNIT_TEST(testReadBuffer);
    CPPUNIT_TEST(testReadBoolean);
    CPPUNIT_TEST(testWriteSigned64);
    CPPUNIT_TEST(testWriteUnsigned64);
    CPPUNIT_TEST(testWriteSigned32);
    CPPUNIT_TEST(testWriteUnsigned32);
    CPPUNIT_TEST(testWriteSigned16);
    CPPUNIT_TEST(testWriteUnsigned16);
    CPPUNIT_TEST(testWriteSigned8);
    CPPUNIT_TEST(testWriteUnsigned8);
    CPPUNIT_TEST(testWriteString);
    CPPUNIT_TEST(testWriteReal32);
    CPPUNIT_TEST(testWriteReal64);
    CPPUNIT_TEST(testWriteBoolean);
    CPPUNIT_TEST(testWriteBuffer);
    CPPUNIT_TEST_SUITE_END();

public:

    void testSetPosition();
    void testGetPosition();
    void testGetSize();
    void testSetSize();
    void testData();
    void testIsEnd();
    void testReset();

    void testReadSigned32();
    void testReadUnsigned32();
    void testReadSigned16();
    void testReadUnsigned16();
    void testReadSigned8();
    void testReadUnsigned8();
    void testReadSigned64();
    void testReadUnsigned64();
    void testReadString();
    void testReadLine();
    void testReadWord();
    void testReadReal32();
    void testReadReal64();
    void testReadBuffer();
    void testReadBoolean();

    void testWriteSigned64();
    void testWriteUnsigned64();
    void testWriteSigned32();
    void testWriteUnsigned32();
    void testWriteSigned16();
    void testWriteUnsigned16();
    void testWriteSigned8();
    void testWriteUnsigned8();
    void testWriteString();
    void testWriteReal32();
    void testWriteReal64();
    void testWriteBoolean();
    void testWriteBuffer();
};

#endif // BUFFER_TEST_H
