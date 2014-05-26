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
		Node();
        explicit Node(ISceneGraph* graph);
        explicit Node(INode* parent);
        virtual ~Node();

		void QueryInterface(const Core::Guid& type, void** object) override;
        void SetAttribute(IAttribute* value) override;
        IAttribute* GetAttribute(const Core::String&, std::uint64_t type) const override;
		int GetAttributesCount(std::uint64_t type) const override;
		std::vector<IAttribute*> GetAttributes(std::uint64_t type) const override;
        void RemoveAttribute(const Core::String& name, std::uint64_t type) override;
        NodeState GetState() const override;
        void SetState(NodeState value) override;
        ISceneGraph* GetSceneGraph() override;
		void SetSceneGraph(ISceneGraph* graph) override;

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
        NodeState m_state {NodeState::Inactive};
        std::uint64_t m_id {0};
        INode* m_parent {nullptr};
        std::vector<INode*> m_children;
        std::map<std::pair<Core::String, std::uint64_t>, IAttribute*> m_attributes;
        ISceneGraph* m_scene_graph {nullptr};
        std::atomic<int> m_delete_count;

		PUNK_OBJECT_DEFAULT_IMPL3(Node)
    };
}
PUNK_ENGINE_END

#endif	//	H_PUNK_SCENE_NODE
