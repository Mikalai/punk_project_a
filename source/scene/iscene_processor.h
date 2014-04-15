#ifndef ISCENE_PROCESSOR_H
#define ISCENE_PROCESSOR_H

#include <config.h>
#include <memory>

PUNK_ENGINE_BEGIN
namespace Core {
    class String;
}
namespace Scene {
    class IGraphProcessor;

    class ISceneProcessor {
    public:
        virtual void SetSceneFile(const Core::String& filename) = 0;
        virtual void RegisterGraphProcessor(IGraphProcessor* proc) = 0;
        virtual void Update(int dt_ms) = 0;
        virtual void DestroyScene() = 0;
        virtual void Terminate() = 0;
    };

    using ISceneProcessorUniquePtr = std::unique_ptr<ISceneProcessor, void (*)(ISceneProcessor*)>;

    PUNK_ENGINE_API ISceneProcessorUniquePtr CreateSceneProcessor();
    PUNK_ENGINE_API void DestroySceneProcessor(ISceneProcessor* processor);
}
PUNK_ENGINE_END

#endif // ISCENE_PROCESSOR_H
