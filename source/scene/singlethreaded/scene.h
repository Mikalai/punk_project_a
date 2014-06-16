#ifndef _H_PUNK_SCENE_MAIN_HEADER
#define _H_PUNK_SCENE_MAIN_HEADER

#include <set>
#include <system/concurrency/thread_mutex.h>
#include <core/object.h>
#include "inode.h"
#include "iscene.h"

PUNK_ENGINE_BEGIN
namespace SceneModule
{
    class PUNK_ENGINE_LOCAL Scene : public IScene {
    public:
		Scene();
        virtual ~Scene();
		void QueryInterface(const Core::Guid& type, void** object) override;
        void Lock() override;
        void Unlock() override;
        INode* GetRoot() override;
        const INode* GetRoot() const override;
        void SetRoot(INode* node) override;
		INode* ReleaseRoot() override;
		void AddObserver(IObserver* observer) override;
		void RemoveObserver(IObserver* observer) override;
		void OnNodeAdded(INode* parent, INode* child) override;
		void OnNodeRemoved(INode* parent, INode* child) override;
		void OnAttributeAdded(INode* node, IAttribute* attribute) override;
		void OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) override;
		void OnAttributeRemoved(INode* node, IAttribute* attribute) override;
		void SetSourcePath(const Core::String& path) override;
		const Core::String GetSourcePath() const override;
    private:
		std::set<IObserver*> m_observers;
        Core::ActionSlot<INode*, INode*> m_on_added_actions;
        Core::ActionSlot<INode*, INode*> m_on_removed_action;
		Core::ActionSlot<INode*, IAttribute*> m_on_attribute_added;
		Core::ActionSlot<INode*, IAttribute*, IAttribute*> m_on_attribute_updated;
		Core::ActionSlot<INode*, IAttribute*> m_on_attribute_removed;

		Core::String m_source_path;

        System::ThreadMutex m_lock;
        INode* m_root {nullptr};

		PUNK_OBJECT_DEFAULT_IMPL(Scene)
    };

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_SCENE_MAIN_HEADER
