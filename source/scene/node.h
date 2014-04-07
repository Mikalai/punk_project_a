#ifndef _H_PUNK_SCENE_NODE
#define _H_PUNK_SCENE_NODE

#include <vector>
#include <map>
#include <string/module.h>
#include "inode.h"

PUNK_ENGINE_BEGIN
namespace Scene
{
    class PUNK_ENGINE_LOCAL Node : public INode {
    public:

        explicit Node(INode* parent = nullptr);
        ~Node();

        void SetAttribute(IAttribute* value) override;
        IAttribute* GetAttribute(const Core::String&, std::uint64_t type) const override;
        void RemoveAttribute(const Core::String& name, std::uint64_t type) override;
        INode* GetParent() override;
        const INode* GetParent() const override;
        std::uint64_t GetChildrenCount() const override;
        INode* GetChild(std::uint64_t index) override;
        const INode* GetChild(std::uint64_t index) const override;
        void AddChild(INode* child) override;
        NodeState GetState() const override;
        void SetState(NodeState value) override;
        void RemoveChild(INode* child, bool depth) override;
        INode* FindChild(IAttribute* attribute, bool depth) override;
        void AddRef() override;
        void Release() override;

    private:
        std::uint64_t m_ref_count;
        NodeState m_state {NodeState::Inactive};
        std::uint64_t m_id {0};
        INode* m_parent {nullptr};
        std::vector<INode*> m_children;
        std::map<std::pair<Core::String, std::uint64_t>, IAttribute*> m_attributes;
    };
}
PUNK_ENGINE_END

#endif	//	H_PUNK_SCENE_NODE
