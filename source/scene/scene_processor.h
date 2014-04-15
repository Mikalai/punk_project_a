#ifndef SCENE_PROCESSOR_H
#define SCENE_PROCESSOR_H

#include <deque>
#include <vector>
#include <system/concurrency/module.h>
#include "iscene_graph.h"
#include "igraph_processor.h"
#include "iscene_processor.h"

PUNK_ENGINE_BEGIN
namespace Scene {

    enum class Code {
        None,
        SetNewScene,
        Update,
        DestroyScene,
        Terminate
    };

    struct SetNewSceneCommand {
        wchar_t m_filepath[MAX_PATH];
    };

    struct UpdateCommand {
        int m_dt;
    };

    struct DestroySceneCommand {

    };

    struct TerminateCommand {

    };

    struct Command {
        Code code;
        union {
            SetNewSceneCommand set_new_scene;
            UpdateCommand update;
            DestroySceneCommand destroy_scene;
            TerminateCommand terminate;
        };
    };

    class SceneProcessor : public ISceneProcessor, System::WorkItem
    {
    public:
        SceneProcessor();
        virtual ~SceneProcessor();
        void Run(void* data) override;
        void SetSceneFile(const Core::String& filename) override;
        void RegisterGraphProcessor(IGraphProcessor* proc) override;
        void Update(int dt_ms) override;
        void DestroyScene() override;
        void Terminate() override;

        void AddCommand(const Command& cmd);
        bool ProcessRequest(const Command& request);

    private:                
        std::vector<IGraphProcessor*> m_proc;
        ISceneGraphUniquePtr m_scene_graph;
        System::Thread m_thread;
        std::deque<Command> m_commands;
        System::Monitor m_lock;
    };
}
PUNK_ENGINE_END


#endif // SCENE_PROCESSOR_H
