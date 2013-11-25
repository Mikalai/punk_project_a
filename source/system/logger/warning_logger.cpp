#include "warning_logger.h"

PUNK_ENGINE_BEGIN
namespace System
{
    WarningLogger::WarningLogger(const Core::String &filename)
        : FileLogger(filename)
    {}

    WarningLogger::~WarningLogger() {}

    void WarningLogger::Write(const Core::String &value)
    {
        Core::String s = Core::String("Warning: {0}").arg(value);
        ConsoleLogger::Write(s);
        FileLogger::Write(s);
    }
}
PUNK_ENGINE_END
