#ifndef _H_PUNK_SYSTEM_LOGGER
#define _H_PUNK_SYSTEM_LOGGER

#include "system/core/object.h"
#include "input/console.h"
#include "clock.h"
#include "../string/string.h"
#include "logger_interface.h"

namespace System
{
    class Logger : public ILogger, public Object
    {
    public:
        void Write(const string& value) override;
        void Connect(LogEvent event) override;

    private:
        std::vector<LogEvent> m_events;
    };
}

#endif	//	_H_PUNK_SYSTEM_LOGGER
