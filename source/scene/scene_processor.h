#ifndef SCENE_PROCESSOR_H
#define SCENE_PROCESSOR_H

#include <vector>
#include "iscene_graph.h"
#include "igraph_processor.h"

PUNK_ENGINE_BEGIN
namespace Scene {
    class SceneProcessor
    {
    public:
        SceneProcessor();
        void RegisterGraphProcessor(IGraphProcessor* proc);
        void Update(int dt_ms);
    private:
        std::vector<IGraphProcessor*> m_proc;
    };
}
PUNK_ENGINE_END


#endif // SCENE_PROCESSOR_H
