#include <deque>
#include <core/object.h>
#include <loader/parser/parse_punk_file.h>
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace Loader
{
    void AsyncParserTask::Run(void*)
    {
        try
        {
            Core::IObject* object = ParsePunkFile(Path());
            SetResult(object);
            State(AsyncParserTask::AsyncSuccess);
            OnComplete(this);
        }
        catch (...)
        {
            State(AsyncParserTask::AsyncFailed);
        }
    }

    AsyncParserTask::AsyncParserTask(Scene::INode* node, const Core::String& path)
        : m_object(nullptr)
        , m_state(AsyncLoading)
        , m_path(path)
        , m_node{node}
    {
        System::GetThreadPool()->EnqueueWorkItem(this);
    }

    Scene::INode* AsyncParserTask::GetNode() const {
        return m_node;
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

    Core::IObject* AsyncParserTask::Release()
    {
        auto res = m_object;
        m_object = nullptr;
        return res;
    }

    void AsyncParserTask::SetResult(Core::IObject *value)
    {
        m_object = value;
    }

    const Core::String& AsyncParserTask::Path() const
    {
        return m_path;
    }
}
PUNK_ENGINE_END
