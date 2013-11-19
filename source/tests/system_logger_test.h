#ifndef SYSTEM_LOGGER_TEST_H
#define SYSTEM_LOGGER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class SystemLoggerTest : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(SystemLoggerTest);
    CPPUNIT_TEST(testOutMessage);
    CPPUNIT_TEST_SUITE_END();

    void testOutMessage();
};

#endif // SYSTEM_LOGGER_TEST_H
