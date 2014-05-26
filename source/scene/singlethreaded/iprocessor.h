#ifndef _H_IPROCESSOR
#define _H_IPROCESSOR

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {

	class ISceneManager;

	DEFINE_PUNK_GUID(IID_IProcessor, "2E907E18-8D08-401E-9C83-0710D9CA0CA4");
	
	class IProcessor : public virtual Core::IObject {
	public:
		virtual void SetSceneManager(ISceneManager* manager) = 0;
		virtual void Update(int dt) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IPROCESSOR