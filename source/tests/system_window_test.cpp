#include "system_window_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SystemWindowTest);

void SystemWindowTest::testCreateWindow()
{
    CPPUNIT_ASSERT(window != nullptr);
    return;
    try
    {
        window = System::GetService<System::Window>("window", "window");
    }
    catch(System::PunkException& e)
    {
        std::wcout << e.ToString() << std::endl;
        throw;
    }    
}

void SystemWindowTest::testDestroyWindow()
{

}

//namespace Test0
//{

//    void Test::Run()
//    {
//        m_result = true;
//        try
//        {
//            System::Window wnd(nullptr);
//            wnd.SetTitle("Test0");
//            wnd.Loop();
//            std::cout << "Window has been closed" << std::endl;
//        }
//        catch(...)
//        {
//           m_result = false;
//        }
//        std::cout << "Test finished" << std::endl;
//    }

//    bool Test::Succeed()
//    {
//        return m_result;
//    }
//}
