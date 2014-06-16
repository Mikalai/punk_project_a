#ifndef _H_ILOADER_PROCESSOR
#define _H_ILOADER_PROCESSOR

#include <config.h>
#include <scene/singlethreaded/iscene_observer.h>

PUNK_ENGINE_BEGIN
namespace IoModule {
	DECLARE_PUNK_GUID(IID_IIoObserver, "B6046EBB-607F-4232-9000-91BB05BE1FF2");

	class IIoObserver : public SceneModule::IObserver {

	};
}
PUNK_ENGINE_END


#endif	//	_H_ILOADER_PROCESSOR