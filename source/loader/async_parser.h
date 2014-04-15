#ifndef PUNK_UTILIT_ASYNC_PARSER_H
#define PUNK_UTILIT_ASYNC_PARSER_H

#include <config.h>
#include <vector>
#include <core/action.h>
#include <string/string.h>
#include <system/concurrency/module.h>

PUNK_ENGINE_BEGIN
namespace Core { class Object; }
namespace Scene { class INode; }
namespace Loader
{
    class PUNK_ENGINE_API AsyncParserTask : public System::WorkItem
    {
    public:
        enum StateType { AsyncLoading, AsyncFailed, AsyncSuccess };

    public:
        AsyncParserTask(Scene::INode* node, const Core::String& path);
        ~AsyncParserTask();

        StateType State();
        void State(StateType state);
        Core::Object* Release();
        const Core::String& Path() const;
        void SetResult(Core::Object* value);
        void Run(void* data) override;
        Scene::INode* GetNode() const;
        Core::ActionSlot<AsyncParserTask*> OnComplete;

    private:
        System::ThreadMutex m_mutex;
        StateType m_state;
        Core::Object* m_object;
        Core::String m_path;        
        Scene::INode* m_node;
    };    
}
PUNK_ENGINE_END

#endif // PUNK_UTILIT_ASYNC_PARSER_H
