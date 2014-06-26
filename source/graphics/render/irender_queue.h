#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

#include <config.h>
#include <core/iobject.h>
#include <graphics/render/irender_context.h>

PUNK_ENGINE_BEGIN
namespace Graphics {

    class Batch;
	class ILowLevelRender;

	struct SelectCriteria {
		bool criteria_all{ false };
		bool criteria_render_policy{ false };
		bool criteria_light_enabled{ false };
		RenderContextType render_context_code{ RenderContextType::NoLightSolidColor };

		static const SelectCriteria SelectAll(){
			SelectCriteria criteria;
			criteria.criteria_all = true;
			return criteria;
		}

		static const SelectCriteria SelectByRenderPolicy(RenderContextType value) {
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
		virtual void Initialize(ILowLevelRender* render) = 0;
		virtual void Add(Batch* m_batch) = 0;
		virtual void Clear() = 0;
		virtual std::vector<Batch*>& GetBatches(RenderContextType policy) = 0;
		virtual void SelectBatches(std::vector<Batch*>& result, const SelectCriteria& criteria) = 0;
	};

	using IRenderQueuePointer = Core::Pointer < IRenderQueue > ;
}
PUNK_ENGINE_END

#endif // RENDER_QUEUE_H
