#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "log_consumer.h"

PUNK_ENGINE_BEGIN
namespace System {
    class PUNK_ENGINE_LOCAL ConsoleConsumer : public ILogConsumer
    {
    public:
        ConsoleConsumer();
        virtual ~ConsoleConsumer();
        void Write(const Core::String &value) override;
    };
}
PUNK_ENGINE_END

#endif // CONSOLE_LOGGER_H
