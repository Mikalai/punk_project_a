#ifndef _H_ISCENE_MODULE_IMPL
#define _H_ISCENE_MODULE_IMPL

#include <system/module/module.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {

	DECLARE_PUNK_GUID(IID_ISceneModule, "D741CD7C-6DB1-43EA-96D4-01CA9DC5B744");

	class ISceneModule : public System::IModule {
	public:
	};
}
PUNK_ENGINE_END

#endif	//	_H_ISCENE_MODULE_IMPL
