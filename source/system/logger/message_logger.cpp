#include "core/component/module.h"
#include "message_logger.h"

PUNK_ENGINE_BEGIN
namespace System
{
    MessageLogger::MessageLogger(const Core::String &filename)
        : FileLogger(filename)
    {
        m_clock = Core::Acquire<IClock>("time", "default_clock", "clock");
    }

    MessageLogger::~MessageLogger()
    {}

    void MessageLogger::Write(const Core::String &value)
    {
        Core::String s = Core::String("{0}: Message> {1}").arg(m_clock->SysTimeNowAsLocal()).arg(value);
        ConsoleLogger::Write(s);
        FileLogger::Write(s);
    }
}
PUNK_ENGINE_END
