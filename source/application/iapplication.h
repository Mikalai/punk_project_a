#ifndef _H_IAPPLICATION
#define _H_IAPPLICATION

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {
	class ISceneManager;
}
namespace Runtime {

	DECLARE_PUNK_GUID(IID_IApplication, "8F21934D-2557-4FC1-8875-B018221BCA60");

	class IApplication : public Core::IObject {
	public:				
		virtual SceneModule::ISceneManager* GetSceneManager() = 0;
		virtual void Run() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IAPPLICATION