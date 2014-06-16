#ifndef ISCENE_GRAPH_H
#define ISCENE_GRAPH_H

#include <core/iobject.h>
#include <core/action.h>
#include <memory>
#include <config.h>

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
        virtual INode* GetRoot() = 0;
        virtual const INode* GetRoot() const = 0;
        virtual void SetRoot(INode* node) = 0;
		virtual INode* ReleaseRoot() = 0;		
		
		virtual void AddObserver(IObserver* observer) = 0;
		virtual void RemoveObserver(IObserver* observer) = 0;

        virtual void OnNodeAdded(INode* parent, INode* child) = 0;
        virtual void OnNodeRemoved(INode* parent, INode* child) = 0;		
		virtual void OnAttributeAdded(INode* node, IAttribute* attribute) = 0;
		virtual void OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) = 0;
		virtual void OnAttributeRemoved(INode* node, IAttribute* attribute) = 0;
		virtual void SetSourcePath(const Core::String& path) = 0;
		virtual const Core::String GetSourcePath() const = 0;

		template<class T>
		INode* FindNodeByAttribute(const Core::String& name) {
			auto root = GetRoot();
			if (root)
				return root->FindChildByAttribute<T>(name);
			return nullptr;
		}
    };

	using ISceneGraphUniquePtr = Core::UniquePtr < IScene > ;

    extern PUNK_ENGINE_API ISceneGraphUniquePtr CreateSceneFromFile(const Core::String& datafolder, const Core::String& file);
    extern PUNK_ENGINE_API ISceneGraphUniquePtr CreateScene();
}
PUNK_ENGINE_END

#endif // ISCENE_GRAPH_H
