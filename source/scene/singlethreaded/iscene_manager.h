#ifndef GRAPH_PROCESSOR_H
#define GRAPH_PROCESSOR_H

#include <config.h>
#include <core/iobject.h>
#include "iscene.h"
#include "command.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

	class INode;
    class IScene;
	class IProcessor;

	DECLARE_PUNK_GUID(IID_ISceneManager, "D8138AD5-F05C-4209-83CF-A21697E0547A");

    class ISceneManager : public Core::IObject {
    public:
		virtual Core::Pointer<IScene> GetScene() = 0;
		virtual void AddProcessor(Core::Pointer<IProcessor> processor) = 0;
		virtual void Update(float dt) = 0;
		virtual void Terminate() = 0;
		virtual bool IsTerminated() const = 0;

		//	processor notifications
		//virtual void SceneChangeStarted(ISceneProcessor* value) = 0;
		//virtual void SceneChangeComplete(ISceneProcessor* value) = 0;
		//virtual void DestructionStarted(ISceneProcessor* value) = 0;
		//virtual void DestructionComplete(ISceneProcessor* value) = 0;		

		//virtual void RequestTermination(ISceneProcessor* suppliant) = 0;		
		//virtual void RequestPause(ISceneProcessor* suppliant) = 0;
		//virtual void Paused(ISceneProcessor* value);
		//virtual void RequestResume(ISceneProcessor* value) = 0;
		//virtual void Resumed(ISceneProcessor* value) = 0;

		//virtual void RequestNodeRemove(ISceneProcessor* suppliant, Core::Pointer<INode> node) = 0;
		//virtual void AllowNodeRemove(ISceneProcessor* processor, Core::Pointer<INode> node) = 0;

		//virtual void RequestNodeAdd(ISceneProcessor* suppliant, Core::Pointer<INode> parent, Core::Pointer<INode> child) = 0;


		//virtual void BeginSceneSync(ISceneProcessor* value) = 0;
		//virtual void EndSceneSync(ISceneProcessor* value) = 0;		

		//virtual void RequestSceneChange(ISceneProcessor* suppliant, IScene* scene) = 0;
    };

}
PUNK_ENGINE_END

#endif // GRAPH_PROCESSOR_H
