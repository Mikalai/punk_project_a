#include "message_logger.h"

namespace System
{
    MessageLogger::MessageLogger(const string &filename)
        : FileLogger(filename)
    {}

    void MessageLogger::Write(const string &value)
    {
        string s = string("Message: {0}").arg(value);
        ConsoleLogger::Write(s);
        FileLogger::Write(s);
    }
}
