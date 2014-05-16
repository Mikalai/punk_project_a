#include <graphics/error/module.h>
#include <graphics/render/render_context/render_context_select.h>
#include "render_queue.h"
#include "render_batch.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
    RenderQueue::RenderQueue()
    {
    }

    void RenderQueue::Clear() {
        for (auto& queue : m_states) {
			while (!queue.empty()) {
				delete queue.back();
				queue.pop_back();
			}
        }
    }

    void RenderQueue::Add(Batch *m_batch) {
        IRenderContext* context = SelectRenderContext(m_batch->m_state);
        if (!context)
            throw Error::GraphicsException(L"RenderContext not supported");
        m_states[(int)context->GetPolicy()].push_back(m_batch);
    }

    std::vector<Batch*>& RenderQueue::GetBatches(RenderPolicySet render_context_code) {
        return m_states[GetIndex(render_context_code)];
    }
}
PUNK_ENGINE_END
