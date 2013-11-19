#ifndef _H_TEST0
#define _H_TEST0

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "punk_engine.h"

class SystemWindowTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SystemWindowTest);
    CPPUNIT_TEST(testCreateWindow);
    CPPUNIT_TEST(testDestroyWindow);
    CPPUNIT_TEST_SUITE_END();

private:
    System::Window* window;

public:
    void testCreateWindow();
    void testDestroyWindow();
};

#endif // _H_TEST0
