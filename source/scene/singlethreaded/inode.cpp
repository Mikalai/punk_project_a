#include <algorithm>
#include <utility>
#include <iostream>
#include <atomic>
#include <vector>
#include <map>
#include <core/iserializable.h>
#include <string/module.h>
#include <system/factory/module.h>
#include <system/concurrency/module.h>
#include <core/iserializable.h>
#include "iscene.h"
#include <string/module.h>
#include "inode.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {	

	class PUNK_ENGINE_LOCAL Node : public INode, public Core::ISerializable {
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
			if (!object)
				return;
			*object = nullptr;
			if (type == Core::IID_IObject) {
				*object = (INode*)this;
				AddRef();
			}
			else if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
			else if (type == IID_INode) {
				*object = this;
				AddRef();
			}
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
		void RemoveChild(Core::Pointer<INode> node) override {
			auto it = std::find(m_children.begin(), m_children.end(), node);
			if (it == m_children.end())
				return;
			m_children.erase(it);
		}

		void RemoveAllChildren() override {
			m_children.clear();
		}

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
			node->SetScene(m_scene_graph);
			if (m_scene_graph) {
				m_scene_graph->OnNodeAdded(Core::Pointer < INode > {this, Core::DestroyObject}, node);
			}
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
			return NodeState::Active;
		}

		void SetState(NodeState value) override {
			//m_state = value;
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

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			//	save clsid
			buffer.WriteBuffer(CLSID_Node.ToPointer(), sizeof(CLSID_Node));
			
			//	save attributes
			std::vector<std::pair<std::pair<Core::String, std::uint64_t>, Core::Pointer<IAttribute>>> serializable_attributes;
			serializable_attributes.reserve(m_attributes.size());
			for (auto& pair : m_attributes) {
				auto data = pair.second->GetRawData();
				if (data) {
					auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(data, Core::IID_ISerializable);	
					if (serializable) {
						serializable_attributes.push_back(pair);

					}
					else {
						System::GetDefaultLogger()->Warning("Data is not serializable in " + pair.first.first);
					}
				}
			}
			std::uint32_t count = (std::uint32_t)serializable_attributes.size();
			buffer.WriteUnsigned32(count);
			for (auto& pair : serializable_attributes) {
				auto data = pair.second->GetRawData();
				auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(data, Core::IID_ISerializable);
				buffer.WriteString(pair.first.first);
				buffer.WriteUnsigned64(pair.first.second);
				serializable->Serialize(buffer);
			}

			//	save childre
			std::vector<Core::Pointer<Core::ISerializable>> serializable_nodes;
			serializable_nodes.reserve(m_children.size());
			for (auto& node : m_children) {
				auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(node, Core::IID_ISerializable);
				if (serializable)
					serializable_nodes.push_back(serializable);
			}

			count = (std::uint32_t)serializable_nodes.size();
			buffer.WriteUnsigned32(count);
			for (auto& node : serializable_nodes) {
				node->Serialize(buffer);
			}
		}

		void Deserialize(Core::Buffer& buffer) override {

			//	save attributes
			
			std::uint32_t count = buffer.ReadUnsigned32();		
			for (std::uint32_t i = 0; i < count; ++i) {
				Core::String name = buffer.ReadString();
				std::uint64_t type = buffer.ReadUnsigned64();
				Core::Guid clsid;
				buffer.ReadBuffer(clsid.ToPointer(), sizeof(clsid));
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				serializable->Deserialize(buffer);				
			}

			//	save childre
			count = buffer.ReadUnsigned32();
			m_children.resize(count);
			for (auto& child : m_children) {
				Core::Guid clsid;
				buffer.ReadBuffer(clsid.ToPointer(), sizeof(clsid));
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				serializable->Deserialize(buffer);
				child = Core::QueryInterfacePtr<INode>(serializable, IID_INode);
			}
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		//NodeState m_state{ NodeState::Inactive };
		//std::uint64_t m_id{ 0 };
		INode* m_parent{ nullptr };
		std::vector<Core::Pointer<INode>> m_children;
		std::map<std::pair<Core::String, std::uint64_t>, Core::Pointer<IAttribute>> m_attributes;
		IScene* m_scene_graph{ nullptr };
		std::atomic<int> m_delete_count;
	};	               				    			
		
    PUNK_REGISTER_CREATOR(CLSID_Node, (System::CreateInstance<Node, INode>));

}
PUNK_ENGINE_END
