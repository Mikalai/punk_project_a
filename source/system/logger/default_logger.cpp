#include <String/module.h>
#include <system/time/module.h>
#include "log_consumer.h"
#include "console_consumer.h"
#include "default_logger.h"

PUNK_ENGINE_BEGIN
namespace System {
    ThreadMutex g_default_logger_lock;
    DefaultLogger* g_default_logger;

    ILogger* GetDefaultLogger() {
        ThreadMutexLock lock(g_default_logger_lock);
        if (!g_default_logger)
            g_default_logger = new DefaultLogger;
        return g_default_logger;
    }

    void DestroyDefaultLogger() {
        ThreadMutexLock lock(g_default_logger_lock);
        delete g_default_logger;
        g_default_logger = nullptr;
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
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Message: " + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Warning(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Warning: " + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Error(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Error: " + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Info(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Info: " + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Write(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Write: " + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }

    void DefaultLogger::Debug(const Core::String& value) {
        ThreadMutexLock lock(m_consumer_mutex);
        Core::String s = m_clock->SysTimeNowAsLocal() + L": Debug: " + value;
        for (auto c : m_consumers) {
            c->Write(s);
        }
    }
}
PUNK_ENGINE_END
