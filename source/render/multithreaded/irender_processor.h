#ifndef _H_IRENDER_PROCESSOR
#define _H_IRENDER_PROCESSOR

#include <config.h>
#include <scene/iscene_processor.h>

PUNK_ENGINE_BEGIN
namespace Render {
		
	DEFINE_PUNK_GUID(IID_ISceneProcessor, "2C586D1B-EF96-49CA-AB81-59581E6B0170");

	class IRenderProcessor : public Scene::ISceneProcessor {

	};
}
PUNK_ENGINE_END

#endif	//	_H_IRENDER_PROCESSOR