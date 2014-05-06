#ifndef RENDER_H
#define RENDER_H

#include <config.h>
#include <system/concurrency/module.h>
#include <graphics/frame/iframe.h>
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
        void SubmitBatch(Batch* batch) override;
        const Math::vec2 FindZRange(const Math::mat4& view) override;
		IFrame* BeginFrame() override;
		void EndFrame() override;

    private:
        RenderQueue* m_queue;
        IVideoDriver* m_driver;
		IFrameUniquePtr m_frame{ nullptr, DestroyFrame };
    };
}
PUNK_ENGINE_END

#endif // RENDER_H
