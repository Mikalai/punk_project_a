#include "logger.h"

namespace System
{
    void Logger::Write(const string &value)
    {
        for (auto e : m_events)
            (*e)(value);
    }

    void Logger::Connect(LogEvent event)
    {
        auto it = std::find(m_events.begin(), m_events.end(), event);
        if (it == m_events.end())
        m_events.push_back(event);
    }
}
