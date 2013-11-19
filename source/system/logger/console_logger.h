#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "logger.h"

namespace System
{
    class PUNK_ENGINE_LOCAL ConsoleLogger : public virtual Logger
    {
    public:
        ConsoleLogger();
        virtual ~ConsoleLogger();
        void Write(const string &value) override;
    };
}

#endif // CONSOLE_LOGGER_H
