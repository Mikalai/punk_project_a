#ifndef GRAPH_PROCESSOR_H
#define GRAPH_PROCESSOR_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Scene {
    class ISceneGraph;
    class IGraphProcessor {
    public:
        virtual void Initialize(ISceneGraph* graph) = 0;

        /**
     * @brief Update process internal structures, doesn't need sync
     * @param dt_ms
     */
        virtual void BeginUpdate(int dt_ms) = 0;
        virtual void WaitUpdateFinish() = 0;

        virtual void Destroy() = 0;
    };
}
PUNK_ENGINE_END

#endif // GRAPH_PROCESSOR_H
