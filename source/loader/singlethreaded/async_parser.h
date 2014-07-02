#ifndef PUNK_UTILIT_ASYNC_PARSER_H
#define PUNK_UTILIT_ASYNC_PARSER_H

#include <config.h>
#include <vector>
#include <core/action.h>
#include <string/string.h>
#include <system/concurrency/module.h>

PUNK_ENGINE_BEGIN
namespace Core { class IObject; }
namespace SceneModule { class INode; }
namespace IoModule
{
    class PUNK_ENGINE_API AsyncParserTask : public System::WorkItem
    {
    public:
        enum StateType { AsyncLoading, AsyncFailed, AsyncSuccess };

    public:
        AsyncParserTask(SceneModule::INode* node, const Core::String& path);
        ~AsyncParserTask();

        StateType State();
        void State(StateType state);
        Core::Pointer<Core::IObject> Release();
        const Core::String& Path() const;
        void SetResult(Core::Pointer<Core::IObject> value);
        void Run(void* data) override;
        SceneModule::INode* GetNode() const;
        Core::ActionSlot<AsyncParserTask*> OnComplete;

    private:
        System::ThreadMutex m_mutex;
        StateType m_state;
		Core::Pointer<Core::IObject> m_object{ nullptr, Core::DestroyObject };
        Core::String m_path;        
        SceneModule::INode* m_node;
    };    
}
PUNK_ENGINE_END

#endif // PUNK_UTILIT_ASYNC_PARSER_H
