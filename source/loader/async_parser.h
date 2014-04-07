#ifndef PUNK_UTILIT_ASYNC_PARSER_H
#define PUNK_UTILIT_ASYNC_PARSER_H

#include <config.h>
#include <string/string.h>
#include <system/concurrency/module.h>

PUNK_ENGINE_BEGIN
namespace Core { class Object; }
namespace Loader
{
    class PUNK_ENGINE_API AsyncParserTask : public System::WorkItem
    {
    public:
        enum StateType { AsyncLoading, AsyncFailed, AsyncSuccess };

    public:
        AsyncParserTask(const Core::String& path);
        ~AsyncParserTask();

        StateType State();
        void State(StateType state);
        Core::Object* Release();
        const Core::String& Path() const;
        void SetResult(Core::Object* value);
        void Run(void* data) override;
    private:
        System::ThreadMutex m_mutex;
        StateType m_state;
        Core::Object* m_object;
        Core::String m_path;
    };    
}
PUNK_ENGINE_END

#endif // PUNK_UTILIT_ASYNC_PARSER_H
