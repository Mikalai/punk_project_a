#include <memory.h>
#include "string/buffer.h"
#include "string/string.h"
#include "buffer_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest);

using namespace Punk::Engine::Core;

void BufferTest::testSetPosition() {
    Buffer buffer;
    CPPUNIT_ASSERT(buffer.GetPosition() == 0);
    buffer.SetPosition(10);
    CPPUNIT_ASSERT(buffer.GetPosition() == 0);
    buffer.SetSize(10);
    buffer.SetPosition(10);
    CPPUNIT_ASSERT(buffer.GetPosition() == 10);
}

void BufferTest::testGetPosition() {
    Buffer buffer;
    CPPUNIT_ASSERT(buffer.GetPosition() == 0);
    buffer.SetPosition(10);
    CPPUNIT_ASSERT(buffer.GetPosition() == 0);
    buffer.SetSize(10);
    buffer.SetPosition(10);
    CPPUNIT_ASSERT(buffer.GetPosition() == 10);
}

void BufferTest::testGetSize() {
    Buffer buffer;
    CPPUNIT_ASSERT(buffer.GetSize() == 0);
    buffer.SetSize(10);
    CPPUNIT_ASSERT(buffer.GetSize() == 10);
    buffer.SetSize(0);
    CPPUNIT_ASSERT(buffer.GetSize() == 0);
}

void BufferTest::testSetSize() {
    Buffer buffer(15);
    CPPUNIT_ASSERT(buffer.GetSize() == 15);
    buffer.SetSize(0);
    CPPUNIT_ASSERT(buffer.GetSize() == 0);
    buffer.SetSize(10);
    CPPUNIT_ASSERT(buffer.GetSize() == 10);
    buffer.SetSize(0);
    CPPUNIT_ASSERT(buffer.GetSize() == 0);
}

void BufferTest::testData() {
    Buffer buffer;
    CPPUNIT_ASSERT(buffer.Data() == nullptr);
    buffer.WriteBoolean(true);
    CPPUNIT_ASSERT(buffer.Data() != nullptr);
}

void BufferTest::testIsEnd() {
    Buffer buffer;
    CPPUNIT_ASSERT(buffer.IsEnd());
    buffer.WriteSigned32(10);
    buffer.Reset();
    CPPUNIT_ASSERT(!buffer.IsEnd());
    CPPUNIT_ASSERT(buffer.ReadSigned32() == 10);
    CPPUNIT_ASSERT(buffer.IsEnd());
}

void BufferTest::testReset() {
    Buffer buffer;
    buffer.WriteReal32(15.0f);
    buffer.Reset();
    float r = buffer.ReadReal32();
    CPPUNIT_ASSERT(r == 15.0f);
}

void BufferTest::testReadSigned32() {
    Buffer buffer;
    int test = 20000000;
    buffer.WriteSigned32(test);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadSigned32() == test);
}

void BufferTest::testReadUnsigned32() {
    Buffer buffer;
    unsigned test = 20000000;
    buffer.WriteUnsigned32(test);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadUnsigned32() == test);
}

void BufferTest::testReadSigned16() {
    Buffer buffer;
    int test = 30000;
    buffer.WriteSigned16(test);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadSigned16() == test);
}

void BufferTest::testReadUnsigned16() {
    Buffer buffer;
    unsigned short test = 30000;
    buffer.WriteUnsigned16(test);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadUnsigned16() == test);
}

void BufferTest::testReadSigned8() {
    Buffer buffer;
    char test = 30;
    buffer.WriteSigned8(test);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadSigned8() == test);
}

void BufferTest::testReadUnsigned8() {
    Buffer buffer;
    unsigned char test = 30;
    buffer.WriteUnsigned8(test);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadUnsigned8() == test);
}

void BufferTest::testReadSigned64() {
    Buffer buffer;
    std::int64_t test = 300000000000000;
    buffer.WriteSigned64(test);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadSigned64() == test);
}

void BufferTest::testReadUnsigned64() {
    Buffer buffer;
    std::uint64_t test = 300000000000000;
    buffer.WriteUnsigned64(test);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadUnsigned64() == test);
}

void BufferTest::testReadString() {
    String test("Hello world");
    Buffer buffer;
    buffer.WriteString(test);
    buffer.Reset();
    String res = buffer.ReadString();
    CPPUNIT_ASSERT(res == test);
    CPPUNIT_ASSERT(buffer.IsEnd());
}

void BufferTest::testReadLine() {
    Buffer buffer;
    char buf[] = "Hello world\nI'm captain Kirk";
    buffer.WriteBuffer(buf, sizeof(buf));
    buffer.Reset();
    String res = buffer.ReadLine();
    CPPUNIT_ASSERT(res == "Hello world");
    res = buffer.ReadLine();
    CPPUNIT_ASSERT(res == "I'm captain Kirk");
}

void BufferTest::testReadWord() {
    Buffer buffer;
    char buf[] = "Hello world";
    buffer.WriteBuffer(buf, sizeof(buf));
    buffer.Reset();
    String res = buffer.ReadWord();
    CPPUNIT_ASSERT(res == "Hello");
    res = buffer.ReadWord();
    CPPUNIT_ASSERT(res == "world");
    CPPUNIT_ASSERT(buffer.IsEnd());
    res = buffer.ReadWord();
    CPPUNIT_ASSERT(res == "");
}

void BufferTest::testReadReal32() {
    Buffer buffer;
    buffer.WriteReal32(1.0f);
    buffer.Reset();
    float r = buffer.ReadReal32();
    CPPUNIT_ASSERT(r == 1.0f);
}

void BufferTest::testReadReal64() {
    Buffer buffer;
    buffer.WriteReal64(1.0);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadReal64() == 1.0);
}

void BufferTest::testReadBuffer() {
    Buffer buffer;
    char test[] = "This is a some kind of buffer";
    char buf[sizeof(test)];
    buffer.WriteBuffer(test, sizeof(test));
    buffer.Reset();
    buffer.ReadBuffer(buf, sizeof(buf));
    CPPUNIT_ASSERT(!memcmp(test, buf, sizeof(buf)));
}

void BufferTest::testReadBoolean() {
    Buffer buffer;
    buffer.WriteBoolean(true);
    buffer.WriteBoolean(false);
    buffer.Reset();
    CPPUNIT_ASSERT(buffer.ReadBoolean());
    CPPUNIT_ASSERT(!buffer.ReadBoolean());
}

void BufferTest::testWriteSigned64() {
}

void BufferTest::testWriteUnsigned64() {

}

void BufferTest::testWriteSigned32() {

}

void BufferTest::testWriteUnsigned32() {

}

void BufferTest::testWriteSigned16() {

}

void BufferTest::testWriteUnsigned16() {

}

void BufferTest::testWriteSigned8() {

}

void BufferTest::testWriteUnsigned8() {

}

void BufferTest::testWriteString() {

}

void BufferTest::testWriteReal32() {

}

void BufferTest::testWriteReal64() {

}

void BufferTest::testWriteBoolean() {

}

void BufferTest::testWriteBuffer() {

}
