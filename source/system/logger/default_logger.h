#ifndef _H_DEFAULE_LOGGER
#define _H_DEFAULE_LOGGER

#include <set>
#include <system/concurrency/thread_mutex.h>
#include "logger_interface.h"

PUNK_ENGINE_BEGIN
namespace System {
    class ConsoleConsumer;
    class IClock;

    class PUNK_ENGINE_LOCAL DefaultLogger : public ILogger {
    public:
        DefaultLogger();
        virtual ~DefaultLogger();
        void Message(const Core::String& value) override;
        void Warning(const Core::String& value) override;
        void Error(const Core::String& value) override;
        void Info(const Core::String& value) override;
        void Write(const Core::String& value) override;
        void Debug(const Core::String& value) override;
        void AddConsumer(ILogConsumer* consumer) override;
        void RemoveConsumer(ILogConsumer* consumer) override;
        void IncreaseOffset() override;
        void DescreaseOffset() override;
    private:
        std::set<ILogConsumer*> m_consumers;
        ThreadMutex m_consumer_mutex;
        IClock* m_clock;
        ConsoleConsumer* m_console_consumer;
        std::uint32_t m_offset{0};
    };
}
PUNK_ENGINE_END

#endif  //  _H_DEFAULE_LOGGER
