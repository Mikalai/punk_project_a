#ifndef ISCENE_PROCESSOR_H
#define ISCENE_PROCESSOR_H

#include <config.h>
#include <memory>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Scene {
	
	class CommandBase;
	class INode;
	class IScene;
	class ISceneManager;

	DEFINE_PUNK_GUID(IID_ISceneProcessor, "C9E4809F-5BC3-4B9F-A58F-F38C84CC473C");

    class ISceneProcessor : public virtual Core::IObject {
    public:		
		virtual void BeginPreProcessSync() = 0;
		virtual void PreProcess() = 0;
		virtual void EndPreProcessSync() = 0;
		virtual void BeginPostProcessSync() = 0;
		virtual void PostProcess() = 0;
		virtual void EndPostProcessSync() = 0;		
		virtual void InternalProcess() = 0;
		virtual void SendAsyncCommand(CommandBase* cmd) = 0;
		virtual void SendSyncCommand(CommandBase* cmd) = 0;
		virtual void WaitComplete() = 0;
		virtual void Terminate() = 0;
    };    
}
PUNK_ENGINE_END

#endif // ISCENE_PROCESSOR_H
