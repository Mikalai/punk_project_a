#ifndef _H_IANIMATOR_PROCESSOR
#define _H_IANIMATOR_PROCESSOR

#include <config.h>
#include <scene/module.h>

PUNK_ENGINE_BEGIN
namespace AnimatorModule {

	DECLARE_PUNK_GUID(IID_IAnimatorProcessor, "27608BB8-FE47-43C1-8AA0-B3D39E14DEA0");

	class PUNK_ENGINE_LOCAL IAnimatorProcessor : public SceneModule::IProcessor {
	public:
	};
}
PUNK_ENGINE_END

#endif //	_H_IANIMATOR_PROCESSOR
