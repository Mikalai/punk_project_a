#include <deque>
#include <core/object.h>
#include <loader/parser/parser.h>
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    void AsyncParserTask::Run(void*)
    {
        try
        {
            Core::Object* object = ParsePunkFile(Path());
            SetResult(object);
            State(AsyncParserTask::AsyncSuccess);
        }
        catch (...)
        {
            State(AsyncParserTask::AsyncFailed);
        }
    }

    AsyncParserTask::AsyncParserTask(const Core::String& path)
        : m_object(nullptr)
        , m_state(AsyncLoading)
        , m_path(path)
    {
        System::GetThreadPool()->EnqueueWorkItem(this);
    }

    AsyncParserTask::~AsyncParserTask()
    {
        delete m_object;
    }

    AsyncParserTask::StateType AsyncParserTask::State()
    {
        System::ThreadMutexLock lock(m_mutex);
        return m_state;
    }

    void AsyncParserTask::State(StateType state)
    {
        System::ThreadMutexLock lock(m_mutex);
        m_state = state;
    }

    Core::Object* AsyncParserTask::Release()
    {
        auto res = m_object;
        m_object = nullptr;
        return res;
    }

    void AsyncParserTask::SetResult(Core::Object *value)
    {
        m_object = value;
    }

    const Core::String& AsyncParserTask::Path() const
    {
        return m_path;
    }

    AsyncParser::AsyncParser()
    {
        m_parse_thread.Create(ParseThread, this);
        m_parse_thread.Resume();
    }

    AsyncParser::~AsyncParser()
    {
        Terminate();
        m_parse_thread.Join();
    }

    void AsyncParser::Add(AsyncParserTask* task)
    {
        m_parse_tasks_monitor.Lock();
        m_tasks.push_back(task);
        m_parse_tasks_monitor.Pulse();
        m_parse_tasks_monitor.Unlock();
    }

    AsyncParserTask* AsyncParser::Next()
    {
        m_parse_tasks_monitor.Lock();
        while (m_tasks.empty())
            m_parse_tasks_monitor.Wait();
        AsyncParserTask* task = m_tasks.front();
        m_tasks.pop_front();
        m_parse_tasks_monitor.Unlock();
        return task;
    }

    void AsyncParser::Terminate()
    {
        m_parse_tasks_monitor.Lock();
        m_tasks.push_front(&g_termination_task);
        m_parse_tasks_monitor.Unlock();
        m_parse_tasks_monitor.Pulse();
    }
}
PUNK_ENGINE_END
