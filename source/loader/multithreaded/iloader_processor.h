#ifndef _H_ILOADER_PROCESSOR
#define _H_ILOADER_PROCESSOR

#include <config.h>
#include <scene/iscene_processor.h>

PUNK_ENGINE_BEGIN
namespace Loader {
	DEFINE_PUNK_GUID(IID_ILoaderProcessor, "B6046EBB-607F-4232-9000-91BB05BE1FF2");

	class ILoaderProcessor : public Scene::ISceneProcessor {

	};
}
PUNK_ENGINE_END


#endif	//	_H_ILOADER_PROCESSOR