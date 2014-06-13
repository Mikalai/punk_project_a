#ifndef ISCENE_PROCESSOR_H
#define ISCENE_PROCESSOR_H

#include <config.h>
#include <memory>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {
	class IAttribute;
	class CommandBase;
	class INode;
	class IScene;
	class ISceneManager;

	DECLARE_PUNK_GUID(IID_IObserver, "C9E4809F-5BC3-4B9F-A58F-F38C84CC473C");

    class IObserver : public Core::IObject {
    public:		
		virtual void SetScene(IScene* value) = 0;
		virtual void OnNodeAdded(INode* parent, INode* child) = 0;
		virtual void OnNodeRemoved(INode* parent, INode* child) = 0;
		virtual void OnAttributeAdded(INode* node, IAttribute* attribute) = 0;
		virtual void OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) = 0;
		virtual void OnAttributeRemoved(INode* node, IAttribute* attribute) = 0;
    };    
}
PUNK_ENGINE_END

#endif // ISCENE_PROCESSOR_H
