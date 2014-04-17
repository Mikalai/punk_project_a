#ifndef _H_PUNK_SCENE_NODE
#define _H_PUNK_SCENE_NODE

#include <atomic>
#include <vector>
#include <map>
#include <string/module.h>
#include "inode.h"

PUNK_ENGINE_BEGIN
namespace Scene
{
    class PUNK_ENGINE_LOCAL Node : public INode {
    public:
        explicit Node(ISceneGraph* graph);
        explicit Node(INode* parent = nullptr);
        virtual ~Node();

        virtual void SetAttribute(IAttribute* value) override;
        virtual IAttribute* GetAttribute(const Core::String&, std::uint64_t type) const override;
        virtual void RemoveAttribute(const Core::String& name, std::uint64_t type) override;
        virtual INode* GetParent() override;
        virtual const INode* GetParent() const override;
        virtual std::uint64_t GetChildrenCount() const override;
        virtual INode* GetChild(std::uint64_t index) override;
        virtual const INode* GetChild(std::uint64_t index) const override;
        virtual void AddChild(INode* child) override;
        virtual NodeState GetState() const override;
        virtual void SetState(NodeState value) override;
        virtual void RemoveChild(INode* child, bool depth) override;
        virtual INode* FindChild(IAttribute* attribute, bool depth) override;
        virtual void AddRef() override;
        virtual void Release() override;
        virtual void Updated(const Core::String& attribute) override;
        virtual void OnUpdate(Core::ActionBase<INode*, const Core::String&>* action) override;
        virtual ISceneGraph* GetSceneGraph() override;

        ///
        /// \brief MarkToDelete
        /// Decrease internal counter
        ///
        void MarkToDelete() override;

        ///
        /// \brief AskToDelete
        /// Increase internal counter
        ///
        void AskToDelete() override;

        ///
        /// \brief CanDelete
        /// \return true when internal counter is zero
        ///
        bool CanDelete() override;

    private:
        std::uint64_t m_ref_count;
        NodeState m_state {NodeState::Inactive};
        std::uint64_t m_id {0};
        INode* m_parent {nullptr};
        std::vector<INode*> m_children;
        std::map<std::pair<Core::String, std::uint64_t>, IAttribute*> m_attributes;
        ISceneGraph* m_scene_graph {nullptr};
        Core::ActionSlot<INode*, const Core::String&> m_on_updated;
        std::atomic<int> m_delete_count;
    };
}
PUNK_ENGINE_END

#endif	//	H_PUNK_SCENE_NODE
