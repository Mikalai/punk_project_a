#ifndef _H_IPROCESSOR
#define _H_IPROCESSOR

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {

	class ISceneManager;

	DECLARE_PUNK_GUID(IID_IProcessor, "2E907E18-8D08-401E-9C83-0710D9CA0CA4");
	
	class IProcessor : public Core::IObject {
	public:
		virtual void SetSceneManager(ISceneManager* manager) = 0;
		virtual void Update(float dt) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IPROCESSOR