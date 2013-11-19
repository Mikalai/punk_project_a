#include "system_logger_test.h"
#include "punk_engine.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SystemLoggerTest);

void SystemLoggerTest::testOutMessage()
{
    System::InitializeComponents();
    out_message().Write(L"Hello world");
    CPPUNIT_ASSERT(true);
    System::DestroyComponents();
}
