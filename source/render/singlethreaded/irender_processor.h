#ifndef _H_IRENDER_PROCESSOR_2
#define _H_IRENDER_PROCESSOR_2

#include <config.h>
#include <scene/module.h>
PUNK_ENGINE_BEGIN
namespace LowLevelRender {

	DECLARE_PUNK_GUID(IID_IRenderProcessor, "3E4A2D17-923C-4E40-ADE5-A2551884BC96");

	class PUNK_ENGINE_LOCAL IRenderProcessor : public SceneModule::IProcessor {
	public:
	};
}
PUNK_ENGINE_END

#endif //	_H_IRENDER_PROCESSOR_2