#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

#include <vector>
#include <array>
#include <config.h>
#include <graphics/render/render_context/irender_context.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class Batch;

    class RenderQueue
    {
    public:
        RenderQueue();
        void Add(Batch* m_batch);
        void Clear();
        std::vector<Batch*>& GetBatches(RenderPolicySet render_context_code);

    private:
		std::array<std::vector<Batch*>, (int)RenderPolicySet::End> m_states;
    };
}
PUNK_ENGINE_END

#endif // RENDER_QUEUE_H
