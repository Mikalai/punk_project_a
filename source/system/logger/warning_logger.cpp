#include "warning_logger.h"

namespace System
{
    WarningLogger::WarningLogger(const string &filename)
        : FileLogger(filename)
    {}

    WarningLogger::~WarningLogger() {}

    void WarningLogger::Write(const string &value)
    {
        string s = string("Warning: {0}").arg(value);
        ConsoleLogger::Write(s);
        FileLogger::Write(s);
    }
}
