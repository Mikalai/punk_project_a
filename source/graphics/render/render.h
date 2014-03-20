#ifndef RENDER_H
#define RENDER_H

#include <config.h>
#include <system/concurrency/module.h>
#include "irender.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    class IFrameBuffer;
    class Batch;
    class RenderQueue;

    class Render : public IRender
    {
    public:
        Render(IVideoDriver* driver);
        virtual ~Render();
        IVideoDriver* GetVideoDriver() override;
        void AsyncBeginRendering(IFrameBuffer* buffer) override;
        void WaitEndRendering() override;
        void SubmitBatch(Batch* batch) override;
        const Math::vec2 FindZRange(const Math::mat4& view) override;
    private:
        RenderQueue* m_queue[2];
        RenderQueue** m_front {nullptr};
        RenderQueue** m_back {nullptr};
        System::ThreadMutex m_queue_mutex;
        IVideoDriver* m_driver;
    };
}
PUNK_ENGINE_END

#endif // RENDER_H
