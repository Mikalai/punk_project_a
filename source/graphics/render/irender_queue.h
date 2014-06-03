#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

#include <config.h>
#include <core/iobject.h>
#include <graphics/render/render_context/irender_context.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class Batch;

	struct SelectCriteria {
		bool criteria_all{ false };
		bool criteria_render_policy{ false };
		bool criteria_light_enabled{ false };
		RenderPolicySet render_context_code{ RenderPolicySet::Solid3D };

		static const SelectCriteria SelectAll(){
			SelectCriteria criteria;
			criteria.criteria_all = true;
			return criteria;
		}

		static const SelectCriteria SelectByRenderPolicy(RenderPolicySet value) {
			SelectCriteria criteria;
			criteria.criteria_render_policy = true;
			criteria.render_context_code = value;
			return criteria;
		}

		static const SelectCriteria SelectByLightEnabled() {
			SelectCriteria criteria;
			criteria.criteria_light_enabled = true;
			return criteria;
		}

	};

	DECLARE_PUNK_GUID(IID_IRenderQueue, "5A25B52E-EC47-4774-BBB7-7252D0D1C461");

	class IRenderQueue : public Core::IObject
	{
	public:
		virtual void Add(Batch* m_batch) = 0;
		virtual void Clear() = 0;
		virtual std::vector<Batch*>& GetBatches(RenderPolicySet policy) = 0;
		virtual void SelectBatches(std::vector<Batch*>& result, const SelectCriteria& criteria) = 0;
	};

	using IRenderQueueUniquePtr = Core::UniquePtr < IRenderQueue > ;
}
PUNK_ENGINE_END

#endif // RENDER_QUEUE_H
