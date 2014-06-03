#include <core/ifactory.h>
#include <graphics/error/module.h>
#include <graphics/render/render_context/render_context_select.h>
#include <vector>
#include <array>
#include "irender_queue.h"
#include "render_batch.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

	class PUNK_ENGINE_LOCAL RenderQueue : public IRenderQueue
	{
	public:
		RenderQueue();
		virtual ~RenderQueue();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IRenderQueue
		void Add(Batch* m_batch) override;;
		void Clear() override;;
		std::vector<Batch*>& GetBatches(RenderPolicySet render_context_code) override;;
		virtual void SelectBatches(std::vector<Batch*>& result, const SelectCriteria& criteria) override;
	private:
		std::array<std::vector<Batch*>, (int)RenderPolicySet::End> m_states;
		std::atomic<std::uint32_t> m_ref_count{ 1 };
	};

	RenderQueue::RenderQueue() {}

	RenderQueue::~RenderQueue() {}

	void RenderQueue::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IRenderQueue });
	}

	std::uint32_t RenderQueue::AddRef() {
		m_ref_count.fetch_add(1);
		return m_ref_count;
	}

	std::uint32_t RenderQueue::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
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

	void RenderQueue::SelectBatches(std::vector<Batch*>& result, const SelectCriteria& criteria) {
		if (criteria.criteria_all) {
			for (auto& rc : m_states) {
				result.insert(result.end(), rc.begin(), rc.end());
			}
			return;
		}

		if (criteria.criteria_render_policy) {
			result = m_states[GetIndex(criteria.render_context_code)];
			return;
		}

		if (criteria.criteria_light_enabled) {
			for (auto& rc : m_states) {
				for (auto& batch : rc) {
					if (batch->m_state->render_state->m_enable_lighting) {
						result.push_back(batch);
					}
				}
			}
			return;
		}
	}

	PUNK_REGISTER_CREATOR(IID_IRenderQueue, Core::CreateInstance<RenderQueue>);
}
PUNK_ENGINE_END
