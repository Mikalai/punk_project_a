#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "logger.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class PUNK_ENGINE_LOCAL ConsoleLogger : public virtual Logger
    {
    public:
        ConsoleLogger();
        virtual ~ConsoleLogger();
        void Write(const Core::String &value) override;
    };
}
PUNK_ENGINE_END

#endif // CONSOLE_LOGGER_H
