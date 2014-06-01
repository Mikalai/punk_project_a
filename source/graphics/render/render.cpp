#include <math/vec2.h>
#include <math/mat4.h>
#include <core/ifactory.h>
#include <graphics/error/module.h>
#include <graphics/frame_buffer/module.h>
#include <graphics/render/render_context/irender_context.h>
#include <system/logger/module.h>
#include "render.h"
#include "render_queue.h"
#include "render_batch.h"

PUNK_ENGINE_BEGIN
namespace Graphics {


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
		if (!m_initialized) {
			m_driver = driver;
			m_queue = new RenderQueue();
			m_initialized = true;
		}
	}

	void LowLevelRender::AssertInitialized() {
		if (!m_initialized)
			throw Error::GraphicsException("Not initialized");
	}

    LowLevelRender::~LowLevelRender()
    {
        m_driver = nullptr;
		if (m_queue) {
			delete m_queue;
			m_queue = nullptr;
		}
    }

    IVideoDriver* LowLevelRender::GetVideoDriver() {
		AssertInitialized();
        return m_driver;
    }

    const Math::vec2 LowLevelRender::FindZRange(const Math::mat4& view) {
		AssertInitialized();
        float min = std::numeric_limits<float>::infinity();
        float max = -std::numeric_limits<float>::infinity();

        for (int i = 0; i < GetIndex(RenderPolicySet::End); ++i) {
            RenderPolicySet rc_code = (RenderPolicySet)i;
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
			Core::GetFactory()->CreateInstance(IID_IFrame, (void**)&m_frame);			
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
		for (int i = 0; i < GetIndex(RenderPolicySet::End); ++i) {
			RenderPolicySet rc_code = (RenderPolicySet)i;
			IRenderContext *rc = GetRenderContext(rc_code);
			if (!rc)
				continue;
			auto& batches = m_queue->GetBatches(rc_code);
//#ifdef _DEBUG
//			if (!batches.empty())
//				log->Info(L"LowLevelRender " + RenderPolicySetToString(rc_code));
//#endif
			for (Batch* batch : batches) {
				IRenderable* renderable = batch->m_renderable;
				CoreState* state = batch->m_state;
				rc->Begin();
				rc->BindParameters(*state);
				renderable->Bind();
				renderable->LowLevelRender();
				renderable->Unbind();
				rc->End();
			}
		}
		m_queue->Clear();
		m_frame.reset();
//#ifdef _DEBUG
//		System::GetDefaultLogger()->Info("End AsyncBeginRendering");
//#endif

	}

    void LowLevelRender::SubmitBatch(Batch *batch) {
		AssertInitialized();
        m_queue->Add(batch);
    }

	PUNK_REGISTER_CREATOR(IID_ILowLevelRender, Core::CreateInstance<LowLevelRender>);

    
}
PUNK_ENGINE_END
