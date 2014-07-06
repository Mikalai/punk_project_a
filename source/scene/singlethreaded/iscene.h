#ifndef ISCENE_GRAPH_H
#define ISCENE_GRAPH_H

#include <core/iobject.h>
#include <core/action.h>
#include <memory>
#include <config.h>
#include "inode.h"

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace SceneModule {

    class INode;
	class IAttribute;
	class IObserver;

	DECLARE_PUNK_GUID(IID_IScene, "3BA9C2DB-27C9-42BD-B3CC-AAEF16A91E19");

    class IScene : public Core::IObject {
    public:
        virtual void Lock() = 0;
        virtual void Unlock() = 0;
		virtual Core::Pointer<INode> GetRoot() = 0;
		virtual const Core::Pointer<INode> GetRoot() const = 0;
        virtual void SetRoot(Core::Pointer<INode> node) = 0;
		
		virtual void AddObserver(Core::Pointer<IObserver> observer) = 0;
		virtual void RemoveObserver(Core::Pointer<IObserver> observer) = 0;

        virtual void OnNodeAdded(Core::Pointer<INode> parent, Core::Pointer<INode> child) = 0;
        virtual void OnNodeRemoved(Core::Pointer<INode> parent, Core::Pointer<INode> child) = 0;		
		virtual void OnAttributeAdded(Core::Pointer<INode> node, Core::Pointer<IAttribute> attribute) = 0;
		virtual void OnAttributeUpdated(Core::Pointer<INode> node, Core::Pointer<IAttribute> old_attribute, Core::Pointer<IAttribute> new_attribute) = 0;
		virtual void OnAttributeRemoved(Core::Pointer<INode> node, Core::Pointer<IAttribute> attribute) = 0;		

		template<class T>
		Core::Pointer<INode> FindNodeByAttribute(const Core::String& name) {
			auto root = GetRoot();
			if (root)
				return root->FindChildByAttribute<T>(name);
			return nullptr;
		}
    };

	//using ISceneGraphPointer = Core::Pointer < IScene > ;

    /*extern PUNK_ENGINE_API ISceneGraphPointer CreateSceneFromFile(const Core::String& datafolder, const Core::String& file);
    extern PUNK_ENGINE_API ISceneGraphPointer CreateScene();*/
}
PUNK_ENGINE_END

#endif // ISCENE_GRAPH_H
