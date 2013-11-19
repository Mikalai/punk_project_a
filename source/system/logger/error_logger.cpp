#include "system/errors/stack_trace.h"
#include "error_logger.h"

namespace System
{
    ErrorLogger::ErrorLogger(const string &filename)
        : FileLogger(filename)
    {}

    ErrorLogger::~ErrorLogger()
    {}

    void ErrorLogger::Write(const string &value)
    {
        Stack stack;
        string error = string("Error: {0}\nLocation:\n{1}").arg(value).arg(stack.GetStackTrace());
        FileLogger::Write(error);
        ConsoleLogger::Write(error);
    }
}
