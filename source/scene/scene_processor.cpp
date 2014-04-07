#include "scene_processor.h"

PUNK_ENGINE_BEGIN
namespace Scene {
    SceneProcessor::SceneProcessor()
    {
    }

    void SceneProcessor::Update(int dt_ms) {
        for (IGraphProcessor* proc : m_proc) {
            proc->BeginUpdate(dt_ms);
        }

        for (IGraphProcessor* proc : m_proc) {
            proc->WaitUpdateFinish();
        }
    }
}
PUNK_ENGINE_END
