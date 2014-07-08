#include <vector>
#include <array>
#include <system/factory/module.h>
#include <graphics/state/module.h>
#include <graphics/error/module.h>
#include "render_context_select.h"
#include "render_batch.h"
#include "irender.h"
#include "irender_queue.h"
#include "irender_context_factory.h"
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
		void Initialize(ILowLevelRender* render) override;
		void Add(Batch* m_batch) override;;
		void Clear() override;;
		std::vector<Batch*>& GetBatches(RenderContextType render_context_code) override;;
		virtual void SelectBatches(std::vector<Batch*>& result, const SelectCriteria& criteria) override;
	private:
		void AssertInitialized();
	private:
		bool m_initialized{ false };
		std::array<std::vector<Batch*>, (int)RenderContextType::TotalCount> m_states;
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		ILowLevelRender* m_render{ nullptr };
	};

	RenderQueue::RenderQueue() {}

	RenderQueue::~RenderQueue() {}

	void RenderQueue::AssertInitialized() {
		if (!m_initialized)
			throw Error::GraphicsException("RenderQueue is not initialized");
	}

	void RenderQueue::Initialize(ILowLevelRender* render) {
		if (!m_initialized) {
			m_render = render;
			m_initialized = true;
		}
	}

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
		AssertInitialized();
		RenderContextType policy = SelectRenderContext(m_batch->m_state);
		auto context = m_render->GetRenderContextFactory()->GetOrCreateContext(policy);
		if (!context)
			throw Error::GraphicsException(L"RenderContext not supported");
		m_states[GetIndex(context->GetType())].push_back(m_batch);
	}

	std::vector<Batch*>& RenderQueue::GetBatches(RenderContextType render_context_code) {
		AssertInitialized();
		return m_states[GetIndex(render_context_code)];
	}

	void RenderQueue::SelectBatches(std::vector<Batch*>& result, const SelectCriteria& criteria) {
		AssertInitialized();
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

	PUNK_REGISTER_CREATOR(IID_IRenderQueue, (System::CreateInstance<RenderQueue, IRenderQueue>));
}
PUNK_ENGINE_END
