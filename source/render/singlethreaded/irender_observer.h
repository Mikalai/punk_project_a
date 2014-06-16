#ifndef _H_IRENDER_PROCESSOR
#define _H_IRENDER_PROCESSOR

#include <config.h>
#include <scene/module.h>

PUNK_ENGINE_BEGIN
namespace LowLevelRender {
		
	DECLARE_PUNK_GUID(IID_IRenderObserver, "2C586D1B-EF96-49CA-AB81-59581E6B0170");

	class IRenderObserver : public SceneModule::IObserver {

	};
}
PUNK_ENGINE_END

#endif	//	_H_IRENDER_PROCESSOR