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

    class LowLevelRender : public ILowLevelRender
    {
    public:
        LowLevelRender();
        virtual ~LowLevelRender();
		
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	ILowLevelRender
		void Initialize(IVideoDriver* driver) override;
        IVideoDriver* GetVideoDriver() override;
        void SubmitBatch(Batch* batch) override;
        const Math::vec2 FindZRange(const Math::mat4& view) override;
		IFrame* BeginFrame() override;
		void EndFrame() override;

    private:
		void AssertInitialized();

		bool m_initialized{ false };
		RenderQueue* m_queue{ nullptr };
		IVideoDriver* m_driver{ nullptr };
		IFrameUniquePtr m_frame{ nullptr, Core::DestroyObject };
		std::atomic<std::uint32_t> m_ref_count{ 1 };
    };
}
PUNK_ENGINE_END

#endif // RENDER_H
