#include <string/module.h>
#include <system/time/module.h>
#include "log_consumer.h"
#include "console_consumer.h"
#include "default_logger.h"

PUNK_ENGINE_BEGIN
namespace System {

#ifdef _DEBUG
    namespace __private {
        LogScope::LogScope(const Core::String& scope)
            : m_scope(scope)
        {
            GetDefaultLogger()->Debug(Core::String("Enter {1}").arg(m_scope));
            GetDefaultLogger()->IncreaseOffset();
        }
        LogScope::~LogScope() {
            GetDefaultLogger()->DescreaseOffset();
            GetDefaultLogger()->Debug(Core::String("Leave {1}").arg(m_scope));
        }
    }
#endif

	ThreadMutex g_default_logger_lock;
	DefaultLogger* g_default_logger;

	extern PUNK_ENGINE_API ILogger* GetDefaultLogger() {
		ThreadMutexLock lock(g_default_logger_lock);
		if (!g_default_logger)
			g_default_logger = new DefaultLogger;
		return g_default_logger;
	}

	extern PUNK_ENGINE_API void DestroyDefaultLogger() {
        ThreadMutexLock lock(g_default_logger_lock);
        delete g_default_logger;
        g_default_logger = nullptr;
    }

    void DefaultLogger::IncreaseOffset() {
        m_offset++;
    }

    void DefaultLogger::DescreaseOffset() {
        m_offset--;
    }

    DefaultLogger::DefaultLogger() {
        m_clock = CreateClock();
        m_console_consumer = new ConsoleConsumer;
        AddConsumer(m_console_consumer);
    }

    DefaultLogger::~DefaultLogger() {
        DestroyClock(m_clock);
        RemoveConsumer(m_console_consumer);
        delete m_console_consumer;
    }

    void DefaultLogger::AddConsumer(ILogConsumer *consumer) {
        ThreadMutexLock lock(m_consumer_mutex);
        m_consumers.insert(consumer);
    }

    void DefaultLogger::RemoveConsumer(ILogConsumer *consumer) {
        ThreadMutexLock lock(m_consumer_mutex);
        m_consumers.erase(consumer);
    }

    void DefaultLogger::Message(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Message: " + Core::String(L' ', 2*m_offset) + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Warning(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Warning: " + Core::String(L' ', 2*m_offset) + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Error(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Error: " + Core::String(L' ', 2*m_offset) + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Info(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Info: " + Core::String(L' ', 2*m_offset) + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Write(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Write: " + Core::String(L' ', 2*m_offset) + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Debug(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Debug: " + Core::String(L' ', 2*m_offset) + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }
}
PUNK_ENGINE_END
