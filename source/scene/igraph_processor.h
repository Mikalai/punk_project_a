#ifndef GRAPH_PROCESSOR_H
#define GRAPH_PROCESSOR_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Scene {

    class ISceneGraph;
    class IGraphProcessor {
    public:
        ///
        /// \brief Initialize
        /// \param graph
        /// Common graph processor stuff
        ///
        virtual void SetGraph(ISceneGraph* graph) = 0;

        ///
        /// \brief BeginUpdate
        /// \param dt_ms
        /// Control internal processing thread
        ///
        virtual void BeginUpdate(int dt_ms) = 0;
        virtual void FinishUpdate() = 0;
        virtual void WaitUpdateStart() = 0;
        virtual void WaitUpdateFinish() = 0;

        ///
        /// \brief StartProcessing
        /// Control processor state
        ///
        virtual void StartProcessing() = 0;
        virtual void StopProcessing() = 0;
        virtual void WaitProcessingComplete() = 0;
    };
}
PUNK_ENGINE_END

#endif // GRAPH_PROCESSOR_H
