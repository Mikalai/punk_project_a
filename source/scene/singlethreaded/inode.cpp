#include <algorithm>
#include <utility>
#include <iostream>
#include <atomic>
#include <vector>
#include <map>
#include <system/factory/module.h>
#include <system/concurrency/module.h>
#include "iscene.h"
#include <string/module.h>
#include "inode.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {	

	class PUNK_ENGINE_LOCAL Node : public INode {
	public:
		Node() {}

		explicit Node(IScene* graph) 
			: m_scene_graph{ graph }
		{
			LOG_FUNCTION_SCOPE;
			if (m_scene_graph)
				m_scene_graph->SetRoot(Core::Pointer < INode > {this, Core::DestroyObject});
		}

		explicit Node(INode* parent)
			: m_parent{ parent } {
			LOG_FUNCTION_SCOPE;
			if (m_parent) {
				m_parent->AddChild(Core::Pointer < INode > {this, Core::DestroyObject});
				m_scene_graph = m_parent->GetSceneGraph();
			}
		}

		virtual ~Node() {
			LOG_FUNCTION_SCOPE;
			m_children.clear();
			m_attributes.clear();
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			LOG_FUNCTION_SCOPE;
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_INode });
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	INode
		int GetAttributesCount() const override {
			LOG_FUNCTION_SCOPE;
			return (int)m_attributes.size();
		}

		Core::Pointer<IAttribute> GetAttribute(int index) override {
			LOG_FUNCTION_SCOPE;
			int count = 0;
			for (auto v : m_attributes) {
				if (count == index)
					return v.second;
				count++;
			}
			return Core::Pointer < IAttribute > {nullptr, Core::DestroyObject};
		}

		void AddChild(Core::Pointer<INode> node) override {
			LOG_FUNCTION_SCOPE;
			node->AddRef();
			m_children.push_back(node);
		}

		std::uint32_t GetChildrenCount() const override {
			LOG_FUNCTION_SCOPE;
			return (std::uint32_t)m_children.size();
		}

		Core::Pointer<INode> GetChild(std::uint32_t index) override {
			LOG_FUNCTION_SCOPE;
			return m_children.at(index);
		}

		void SetAttribute(Core::Pointer<IAttribute> value) override {
			LOG_FUNCTION_SCOPE;
			auto key = std::pair<Core::String, std::uint64_t>(value->GetName(), value->GetTypeID());
			auto old = m_attributes[key];
			m_attributes[key] = value;
			if (m_scene_graph) {
				if (old.get() == nullptr)
					m_scene_graph->OnAttributeAdded(Core::Pointer < INode > {this, Core::DestroyObject}, value);
				else {
					m_scene_graph->OnAttributeUpdated(Core::Pointer < INode > {this, Core::DestroyObject}, old, value);
				}
			}
		}

		Core::Pointer<IAttribute> GetAttribute(const Core::String& name, std::uint64_t type) const override {			
			LOG_FUNCTION_SCOPE;
			try {
				return m_attributes.at(std::pair<Core::String, std::uint64_t>(name, type));
			}
			catch (...) {
				return Core::Pointer < IAttribute > {nullptr, Core::DestroyObject};
			}
		}

		Core::Pointer<IAttribute> GetAttribute(std::uint64_t type, std::uint32_t index) const override {
			LOG_FUNCTION_SCOPE;
			try {
				std::uint32_t i = 0;
				for (auto& p : m_attributes) {
					if (p.first.second == type){
						if (i == index) {
							return p.second;
						}
						++i;
					}
				}
			}
			catch (...) {
				return Core::Pointer < IAttribute > {nullptr, Core::DestroyObject};
			}
			return Core::Pointer < IAttribute > {nullptr, Core::DestroyObject};
		}

		int GetAttributesCount(std::uint64_t type) const override {
			LOG_FUNCTION_SCOPE;
			int count = 0;
			for (auto& p : m_attributes) {
				if (p.first.second == type)
					count++;
			}
			return count;
		}

		std::vector<Core::Pointer<IAttribute>> GetAttributes(std::uint64_t type) const override {
			LOG_FUNCTION_SCOPE;
			std::vector<Core::Pointer<IAttribute>> attributes;
			for (auto& p : m_attributes) {
				if (p.first.second == type)
					attributes.push_back(p.second);
			}
			return attributes;
		}

		void RemoveAttribute(const Core::String& name, std::uint64_t type) override {
			LOG_FUNCTION_SCOPE;
			try {
				auto it = m_attributes.find(std::pair<Core::String, std::uint64_t>(name, type));
				if (it != m_attributes.end())
					m_attributes.erase(it);
			}
			catch (...) {
			}
		}

		NodeState GetState() const override {
			LOG_FUNCTION_SCOPE;
			return m_state;
		}

		void SetState(NodeState value) override {
			m_state = value;
		}

		IScene* GetSceneGraph() override {
			return m_scene_graph;
		}

		void SetScene(IScene* graph) override {
			LOG_FUNCTION_SCOPE;
			m_scene_graph = graph;
			for (auto child : m_children) {
				child->SetScene(graph);
			}
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		NodeState m_state{ NodeState::Inactive };
		std::uint64_t m_id{ 0 };
		INode* m_parent{ nullptr };
		std::vector<Core::Pointer<INode>> m_children;
		std::map<std::pair<Core::String, std::uint64_t>, Core::Pointer<IAttribute>> m_attributes;
		IScene* m_scene_graph{ nullptr };
		std::atomic<int> m_delete_count;
	};	               				    			
		
    PUNK_REGISTER_CREATOR(IID_INode, (System::CreateInstance<Node, INode>));

}
PUNK_ENGINE_END
