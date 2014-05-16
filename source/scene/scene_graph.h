#ifndef _H_PUNK_SCENE_MAIN_HEADER
#define _H_PUNK_SCENE_MAIN_HEADER

#include <system/concurrency/thread_mutex.h>
#include <core/object.h>
#include "inode.h"
#include "iscene_graph.h"

PUNK_ENGINE_BEGIN
namespace Scene
{
    class PUNK_ENGINE_LOCAL SceneGraph : public ISceneGraph {
    public:
        virtual ~SceneGraph();
		void QueryInterface(const Core::Guid& type, void** object) override;
        virtual void Lock() override;
        virtual void Unlock() override;
        virtual INode* GetRoot() override;
        virtual const INode* GetRoot() const override;
        virtual void SetRoot(INode* node) override;
		virtual INode* ReleaseRoot() override;
		virtual void SubscribeOnNodeAdded(Core::ActionBase<INode*, INode*>* value) override;
		virtual void SubscribeOnNodeRemoved(Core::ActionBase<INode*, INode*>* value) override;
		virtual void SubscribeOnAttributeAdded(Core::ActionBase<INode*, IAttribute*>* value) override;
		virtual void SubscribeOnAttributeUpdated(Core::ActionBase<INode*, IAttribute*, IAttribute*>* value) override;
		virtual void SubscribeOnAttributeRemoved(Core::ActionBase<INode*, IAttribute*>* value) override;
		virtual void OnNodeAdded(INode* parent, INode* child) override;
		virtual void OnNodeRemoved(INode* parent, INode* child) override;
		virtual void OnAttributeAdded(INode* node, IAttribute* attribute) override;
		virtual void OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) override;
		virtual void OnAttributeRemoved(INode* node, IAttribute* attribute) override;
		virtual void SetSourcePath(const Core::String& path) override;
		virtual const Core::String GetSourcePath() const override;
    private:
        Core::ActionSlot<INode*, INode*> m_on_added_actions;
        Core::ActionSlot<INode*, INode*> m_on_removed_action;
		Core::ActionSlot<INode*, IAttribute*> m_on_attribute_added;
		Core::ActionSlot<INode*, IAttribute*, IAttribute*> m_on_attribute_updated;
		Core::ActionSlot<INode*, IAttribute*> m_on_attribute_removed;

		Core::String m_source_path;

        System::ThreadMutex m_lock;
        INode* m_root {nullptr};

		PUNK_OBJECT_DEFAULT_IMPL3(SceneGraph)
    };

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SCENE_MAIN_HEADER
