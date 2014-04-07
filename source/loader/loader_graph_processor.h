#ifndef LOADER_GRAPH_PROCESSOR_H
#define LOADER_GRAPH_PROCESSOR_H

#include <list>
#include <config.h>
#include <scene/module.h>
#include "async_parser.h"

PUNK_ENGINE_BEGIN
namespace Loader {
    class LoaderCache;

    class PUNK_ENGINE_API LoaderGraphProcessor : public Scene::IGraphProcessor
    {
    public:
        LoaderGraphProcessor();
        void Initialize(Scene::ISceneGraph* graph) override;
        void BeginUpdate(int dt_ms) override;
        void WaitUpdateFinish() override;
        void Destroy() override;

        void PreUpdate();
        void PostUpdate();
        void Process(Scene::INode* node);
        void InternalUpdate(int dt_ms);
        bool IsFinish();
        void WaitUpdate();
        void EndUpdate();

    public:
        int m_last_update_step;
        Scene::ISceneGraph* m_graph {nullptr};
        AsyncParser* m_parser {nullptr};
        std::list<LoaderCache*> m_caches;
        std::vector<LoaderCache*> m_complete;
        System::ThreadMutex m_update_mutex;
    };
}
PUNK_ENGINE_END

#endif // LOADER_GRAPH_PROCESSOR_H
