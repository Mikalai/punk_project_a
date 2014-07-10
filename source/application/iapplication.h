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
	DECLARE_PUNK_GUID(CLSID_Application, "E547163C-8680-46A9-B2FD-07F27F2A8A73");

	class IApplication : public Core::IObject {
	public:				
		virtual Core::Pointer<SceneModule::ISceneManager> GetSceneManager() = 0;
		virtual void Run() = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IAPPLICATION