#ifndef _H_IANIMATOR_OBSERVER
#define _H_IANIMATOR_OBSERVER

#include <config.h>
#include <scene/module.h>

PUNK_ENGINE_BEGIN
namespace AnimatorModule {

	DECLARE_PUNK_GUID(IID_IAnimatorObserver, "334FA429-5EF4-4ED6-81F1-DA290DD35C72");

	class IAnimatorObserver : public SceneModule::IObserver {

	};
}
PUNK_ENGINE_END

#endif	//	_H_IRENDER_PROCESSOR