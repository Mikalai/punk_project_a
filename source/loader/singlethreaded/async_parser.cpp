#include <deque>
#include <core/object.h>
#include <loader/parser/parse_punk_file.h>
#include <scene/singlethreaded/inode.h>
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace IoModule
{
    void AsyncParserTask::Run(void*)
    {
        try
        {
            auto object = ParsePunkFile(Path());
            SetResult(object);
            State(AsyncParserTask::AsyncSuccess);
            OnComplete(this);
        }
        catch (...)
        {
            State(AsyncParserTask::AsyncFailed);
        }
    }

    AsyncParserTask::AsyncParserTask(Core::Pointer<SceneModule::INode> node, const Core::String& path)
        : m_object(nullptr, Core::DestroyObject)
        , m_state(AsyncLoading)
        , m_path(path)
        , m_node{node}
    {
        System::GetThreadPool()->EnqueueWorkItem(this);
    }

    Core::Pointer<SceneModule::INode> AsyncParserTask::GetNode() const {
        return m_node;
    }

    AsyncParserTask::~AsyncParserTask()
    {}

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

    Core::Pointer<Core::IObject> AsyncParserTask::Release()
    {
        auto res = m_object;
		m_object.reset(nullptr);
        return res;
    }

    void AsyncParserTask::SetResult(Core::Pointer<Core::IObject> value)
    {
        m_object = value;
    }

    const Core::String& AsyncParserTask::Path() const
    {
        return m_path;
    }
}
PUNK_ENGINE_END
