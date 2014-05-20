#ifndef _H_ISCENE_WORKER
#define _H_ISCENE_WORKER

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Scene {
	
	class ISceneProcessor;

	DEFINE_PUNK_GUID(IID_ISceneWorker, "F7365F8D-0B41-40B2-BA40-406490692F7F");

	class ISceneWorker : public virtual Core::IObject {
	public:
		virtual void SetProcessor(ISceneProcessor* value) = 0;
		virtual ISceneProcessor* GetProcessor() const = 0;
		virtual bool IsFinish() const = 0;
		virtual void WaitProcessStart() = 0;
		virtual void PreProcess() = 0;
		virtual void Process() = 0;
		virtual void PostProcess() = 0;
		virtual void IndicateProcessComplete() = 0;
	};

}
PUNK_ENGINE_END

#endif	//	_H_ISCENE_WORKER