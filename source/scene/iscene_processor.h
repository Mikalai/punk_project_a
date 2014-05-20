#ifndef ISCENE_PROCESSOR_H
#define ISCENE_PROCESSOR_H

#include <config.h>
#include <memory>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Scene {
	
	class INode;
	class IScene;
	class ISceneManager;

	DEFINE_PUNK_GUID(IID_ISceneProcessor, "C9E4809F-5BC3-4B9F-A58F-F38C84CC473C");

    class ISceneProcessor : public virtual Core::IObject {
    public:
		virtual void Initialize(ISceneManager* value) = 0;
		virtual void Destroy(ISceneManager* value) = 0;
		virtual void ChangeScene(IScene* value) = 0;		
		virtual void OnNodeAdded(INode* parent, INode* child) = 0;
		virtual void OnTimeAdvanced(int dt) = 0;
    };    
}
PUNK_ENGINE_END

#endif // ISCENE_PROCESSOR_H
