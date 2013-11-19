#include <iostream>
#include "console_logger.h"

namespace System
{
    ConsoleLogger::ConsoleLogger()
    {}

    void ConsoleLogger::Write(const string &value)
    {
        std::wcout << value << std::endl;
    }
}
