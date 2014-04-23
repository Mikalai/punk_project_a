#ifndef _H_PUNK_SCENE_MAIN_HEADER
#define _H_PUNK_SCENE_MAIN_HEADER

#include <system/concurrency/thread_mutex.h>
#include <core/object.h>
#include "inode.h"
#include "iscene_graph.h"

PUNK_ENGINE_BEGIN
namespace Scene
{
    class PUNK_ENGINE_LOCAL SceneGraph : public ISceneGraph, public Core::Object {
    public:
        virtual ~SceneGraph();
        virtual void Lock() override;
        virtual void Unlock() override;
        virtual INode* GetRoot() override;
        virtual const INode* GetRoot() const override;
        virtual void SetRoot(INode* node) override;
		virtual INode* ReleaseRoot() override;
        virtual void AddNodeAddedAction(Core::ActionBase<INode*, INode*>* value) override;
        virtual void AddNodeRemovedAction(Core::ActionBase<INode*, INode*>* value) override;
        virtual void OnNodeAdded(INode* parent, INode* child) override;
        virtual void OnNodeRemoved(INode* parent, INode* child) override;
    private:
        Core::ActionSlot<INode*, INode*> m_on_added_actions;
        Core::ActionSlot<INode*, INode*> m_on_removed_action;
        System::ThreadMutex m_lock;
        INode* m_root {nullptr};

		PUNK_OBJECT(SceneGraph)
    };

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SCENE_MAIN_HEADER
