#include <math/vec2.h>
#include <math/mat4.h>
#include <graphics/frame_buffer/module.h>
#include <graphics/render/render_context/irender_context.h>
#include <system/logger/module.h>
#include "render.h"
#include "render_queue.h"
#include "render_batch.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    Render::Render(IVideoDriver* driver)
    : m_driver{driver}
    {
        m_queue[0] = new RenderQueue();
        m_queue[1] = new RenderQueue();
        m_front = &m_queue[0];
        m_back = &m_queue[1];
    }

    Render::~Render()
    {
        m_driver = nullptr;
        delete m_queue[0];
        delete m_queue[1];
        m_front = m_back = nullptr;
    }

    IVideoDriver* Render::GetVideoDriver() {
        return m_driver;
    }

    void Render::AsyncBeginRendering(IFrameBuffer *buffer)
    {
#ifdef _DEBUG
        System::ILogger* log = System::GetDefaultLogger();
        log->Info("Begin AsyncBeginRendering");
#endif
        System::ThreadMutexLock lock(m_queue_mutex);
        std::swap(*m_front, *m_back);
        for (int i = 0; i < GetIndex(RenderPolicySet::End); ++i) {
            RenderPolicySet rc_code = (RenderPolicySet)i;
            IRenderContext *rc = GetRenderContext(rc_code);
            if (!rc)
                continue;
            auto& batches = (*m_front)->GetBatches(rc_code);            
#ifdef _DEBUG
            if (!batches.empty())
                log->Info(L"Render " + RenderPolicySetToString(rc_code));
#endif
            for (Batch* batch : batches) {
                IRenderable* renderable = batch->m_renderable;
                CoreState* state = batch->m_state;
                rc->Begin();
                rc->BindParameters(*state);
                renderable->Bind(rc->GetRequiredAttributesSet());
                renderable->Render();
                renderable->Unbind();
                rc->End();
            }
        }        
        (*m_front)->Clear();
#ifdef _DEBUG
        System::GetDefaultLogger()->Info("End AsyncBeginRendering");
#endif
    }

    void Render::WaitEndRendering() {
        System::ThreadMutexLock lock(m_queue_mutex);        
        m_queue_mutex.Unlock();
    }

    const Math::vec2 Render::FindZRange(const Math::mat4& view) {
        float min = std::numeric_limits<float>::infinity();
        float max = -std::numeric_limits<float>::infinity();

        for (int i = 0; i < GetIndex(RenderPolicySet::End); ++i) {
            RenderPolicySet rc_code = (RenderPolicySet)i;
            auto& batches = (*m_back)->GetBatches(rc_code);
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

    void Render::SubmitBatch(Batch *batch) {
        (*m_back)->Add(batch);
    }

    extern PUNK_ENGINE_API IRenderUniquePtr CreateRender(IVideoDriver* driver) {
        return IRenderUniquePtr{new Render(driver), DestroyRender};
    }

    extern PUNK_ENGINE_API void DestroyRender(IRender* value) {
        Render* r = dynamic_cast<Render*>(value);
        delete r;
    }
}
PUNK_ENGINE_END
