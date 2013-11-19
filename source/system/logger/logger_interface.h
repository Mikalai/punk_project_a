#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include "config.h"
#include "system/action.h"

namespace System
{
    using LogEvent = ActionBasePtr<const string&>;

    class ILogger
    {
    public:
        virtual void Write(const string& value) = 0;
        virtual void Connect(LogEvent event) = 0;
    };
}

extern PUNK_ENGINE_API System::ILogger& out_error();
extern PUNK_ENGINE_API System::ILogger& out_message();
extern PUNK_ENGINE_API System::ILogger& out_warning();

#endif // LOGGER_INTERFACE_H
