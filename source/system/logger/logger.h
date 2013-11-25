#ifndef _H_PUNK_SYSTEM_LOGGER
#define _H_PUNK_SYSTEM_LOGGER

#include "core/object.h"
#include "string/string.h"
#include "logger_interface.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class Logger : public ILogger, public Core::Object
    {
    public:
        void Write(const Core::String& value) override;
        void Connect(LogEvent event) override;

    private:
        std::vector<LogEvent> m_events;
    };
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SYSTEM_LOGGER
