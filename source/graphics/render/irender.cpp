#include <config.h>
#include <system/concurrency/module.h>
#include <graphics/frame/iframe.h>
#include <graphics/primitives/module.h>
#include <graphics/video_driver/module.h>
#include "irender.h"
#include <math/vec2.h>
#include <math/mat4.h>
#include <system/factory/module.h>
#include <graphics/error/module.h>
#include <graphics/frame_buffer/module.h>
#include <graphics/render/irender_context.h>
#include <system/logger/module.h>
#include "irender_queue.h"
#include "irender_context_factory.h"
#include "render_batch.h"

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
		IRenderQueue* GetRenderQueue() override;
		IRenderContextFactory* GetRenderContextFactory() override { return m_rc_factory.get(); }

	private:
		void AssertInitialized();

		bool m_initialized{ false };
		IRenderContextFactoryPointer m_rc_factory{ nullptr, Core::DestroyObject };
		IRenderQueuePointer m_queue{ nullptr, Core::DestroyObject };
        Core::Pointer<IVideoDriver> m_driver{ nullptr, Core::DestroyObject };
		IFramePointer m_frame{ nullptr, Core::DestroyObject };
		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};

	void LowLevelRender::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject) {
			*object = (void*)(Core::IObject*)this;
			AddRef();
			return;
		}
		else if (type == IID_ILowLevelRender) {
			*object = (void*)(ILowLevelRender*)this;
			AddRef();
			return;
		}
	}

	std::uint32_t LowLevelRender::AddRef() {
		m_ref_count.fetch_add(1);
		return m_ref_count;
	}

	std::uint32_t LowLevelRender::Release() {
		if (!(m_ref_count.fetch_sub(1)-1)) {
			delete this; \
		}
		return m_ref_count;
	}

    LowLevelRender::LowLevelRender()
    {        
    }

	void LowLevelRender::Initialize(IVideoDriver* driver) {
        if (!driver)
            throw Error::GraphicsException("Can't initialize low level render with null driver");
		if (!m_initialized) {            
            driver->AddRef();
            m_driver.reset(driver);
            m_queue = System::CreateInstancePtr<IRenderQueue>(IID_IRenderQueue);
			m_queue->Initialize(this);
            m_rc_factory = System::CreateInstancePtr<IRenderContextFactory>(IID_IRenderContextFactory);
			m_rc_factory->Initialize(driver);
			m_initialized = true;
		}
        else {
            throw Error::GraphicsException("Low level render has been already initialized");
        }
	}

	void LowLevelRender::AssertInitialized() {
		if (!m_initialized)
			throw Error::GraphicsException("Not initialized");
	}

    LowLevelRender::~LowLevelRender()
    {}

    IVideoDriver* LowLevelRender::GetVideoDriver() {
		AssertInitialized();
        return m_driver.get();
    }

    const Math::vec2 LowLevelRender::FindZRange(const Math::mat4& view) {
		AssertInitialized();
        float min = std::numeric_limits<float>::infinity();
        float max = -std::numeric_limits<float>::infinity();

        for (int i = 0; i < GetIndex(RenderContextType::TotalCount); ++i) {
            RenderContextType rc_code = (RenderContextType)i;
            auto& batches = m_queue->GetBatches(rc_code);
            for (Batch* o : batches) {
                auto transf = view*o->m_state->batch_state->m_bsphere.GetCenter();
                if (transf.Z() + o->m_state->batch_state->m_bsphere.GetRadius() > max)
                    max = transf.Z() + o->m_state->batch_state->m_bsphere.GetRadius();
                if (transf.Z() - o->m_state->batch_state->m_bsphere.GetRadius() < min)
                    min = transf.Z() - o->m_state->batch_state->m_bsphere.GetRadius();
            }
        }
        return Math::vec2(min, max);
    }

	IFrame* LowLevelRender::BeginFrame() {
		AssertInitialized();
		if (!m_frame.get()) {			
            m_frame = System::CreateInstancePtr<IFrame>(IID_IFrame);
			m_frame->SetRender(this);
		}
		return m_frame.get();
	}

	void LowLevelRender::EndFrame() {
		AssertInitialized();
//#ifdef _DEBUG
//		System::ILogger* log = System::GetDefaultLogger();
//		log->Info("Begin AsyncBeginRendering");
//#endif				
		for (int i = 0; i < GetIndex(RenderContextType::TotalCount); ++i) {
			RenderContextType rc_code = (RenderContextType)i;
			IRenderContext *rc = m_rc_factory->GetOrCreateContext(rc_code);
			if (!rc)
				continue;
			auto& batches = m_queue->GetBatches(rc_code);
//#ifdef _DEBUG
//			if (!batches.empty())
//				log->Info(L"LowLevelRender " + RenderPolicySetToString(rc_code));
//#endif
			for (Batch* batch : batches) {
				auto renderable = batch->m_renderable;
				CoreState* state = batch->m_state;
				rc->Begin();
				rc->ApplyState(*state);
				renderable->Bind();
				renderable->LowLevelRender();
				renderable->Unbind();
				rc->End();
			}
		}
		m_queue->Clear();
//#ifdef _DEBUG
//		System::GetDefaultLogger()->Info("End AsyncBeginRendering");
//#endif

	}

    void LowLevelRender::SubmitBatch(Batch *batch) {
		AssertInitialized();
        m_queue->Add(batch);
    }

	IRenderQueue* LowLevelRender::GetRenderQueue() {
		return m_queue.get();
	}

	PUNK_REGISTER_CREATOR(IID_ILowLevelRender, (System::CreateInstance<LowLevelRender, ILowLevelRender>));

    
}
PUNK_ENGINE_END
