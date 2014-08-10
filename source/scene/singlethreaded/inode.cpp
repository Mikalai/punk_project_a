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
			System::GetDefaultLogger()->Debug(L"Node has been destroyed");
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
		INode* GetParent() {
			return m_parent;
		}

		const INode* GetParent() const {
			return m_parent;
		}

		void SetParent(INode* node) {
			if (node == m_parent)
				return;

			if (m_parent) {
				m_parent->RemoveChild(Core::Pointer < INode > {this, Core::DestroyObject});
			}

			m_parent = node;
			if (m_parent) {
				m_parent->AddChild(Core::Pointer < INode > {this, Core::DestroyObject});
			}
		}

		void RemoveChild(Core::Pointer<INode> node) override {
			auto it = std::find(m_children.begin(), m_children.end(), node);
			if (it == m_children.end())
				return;
			m_children.erase(it);
			node->SetParent(nullptr);
		}

		void RemoveAllChildren() override {
			while (!m_children.empty()) {
				RemoveChild(m_children.back());
			}			
		}

		Core::Pointer<IAttribute> GetAttribute(std::uint32_t index) const override {
			return m_attributes.at(index);
		}

		void AddChild(Core::Pointer<INode> node) override {
			if (!node)
				return;

			if (node->GetParent() == this)
				return;

			//node->AddRef();
			m_children.push_back(node);
			node->SetParent(this);
			node->SetScene(m_scene_graph);
			if (m_scene_graph) {
				m_scene_graph->OnNodeAdded(Core::Pointer < INode > {this, Core::DestroyObject}, node);
			}
		}

		std::uint32_t GetChildrenCount() const override {
			return (std::uint32_t)m_children.size();
		}

		Core::Pointer<INode> GetChild(std::uint32_t index) override {
			return m_children.at(index);
		}

		void AddAttribute(Core::Pointer<IAttribute> value) override {

			//	check input
			if (!value) {
				System::GetDefaultLogger()->Error("Can't add empty attribute");
				return;
			}

			auto it = std::find(m_attributes.begin(), m_attributes.end(), value);
			if (it != m_attributes.end()) {
				System::GetDefaultLogger()->Error("Attribute " + value->GetName() + " already added");
				return;
			}
			auto it2 = m_name_cache.find(value->GetName());
			if (it2 != m_name_cache.end()) {
				System::GetDefaultLogger()->Error("Attribute with name " + value->GetName() + " already in node");
				return;
			}

			//	add to main collection
			m_attributes.push_back(value);
			value->SetOwner(this);

			//	add to name cache
			m_name_cache[value->GetName()] = (std::uint32_t)(m_attributes.size() - 1);

			//	notify
			auto index = (std::uint32_t)(m_attributes.size() - 1);
			if (m_scene_graph) {
				m_scene_graph->OnAttributeAdded(Core::Pointer < INode > {this, Core::DestroyObject}, value);
			}

			m_invalid_cache = true;
		}

		void CacheAttribute(const Core::Guid& iid) override {
			for (int i = 0, max_i = GetAttributesCount(); i < max_i; ++i) {
				auto o = Core::QueryInterfacePtr<Core::IObject>(m_attributes[i]->GetRawData(), iid);
				if (o) {
					//	check was it added
					auto it = std::find(m_interface_map[i].begin(), m_interface_map[i].end(), iid);
					if (it == m_interface_map[i].end()) {
						m_attributes_cache[iid].push_back(m_attributes[i]);
						m_interface_map[i].push_back(iid);
					}
				}
			}
			m_invalid_cache = false;
		}

		Core::Pointer<IAttribute> GetAttribute(const Core::Guid& iid, std::uint32_t index) const {
			if (m_invalid_cache)
				const_cast<Node*>(this)->CacheAttribute(iid);
			auto it = m_attributes_cache.find(iid);
			if (it == m_attributes_cache.end()) {				
				if (it == m_attributes_cache.end())
					return Core::Pointer < IAttribute > {nullptr, Core::DestroyObject};				
			}			
			return it->second.at(index);
		}

		Core::Pointer<IAttribute> GetAttribute(const Core::String& name) const override {
			try {
				auto index = GetAttributeIndex(name);
				return GetAttribute(index);
			}
			catch (...) {
				return Core::Pointer < IAttribute > {nullptr, Core::DestroyObject};
			}
		}

		std::uint32_t GetAttributeIndex(const Core::String& name) const {
			for (std::uint32_t i = 0, max_i = GetAttributesCount(); i < max_i; ++i) {
				if (m_attributes[i]->GetName() == name)
					return i;
			}
			return (std::uint32_t) - 1;
		}

		std::uint32_t GetAttributesCount(const Core::Guid& iid) const override {
			if (m_invalid_cache)
				const_cast<Node*>(this)->CacheAttribute(iid);					
			auto it = m_attributes_cache.find(iid);
			if (it == m_attributes_cache.end()) {				
				if (it == m_attributes_cache.end())
					return 0;
			}			
			return (std::uint32_t)it->second.size();
		}

		std::uint32_t GetAttributesCount() const override {
			return (std::uint32_t)m_attributes.size();
		}

		std::vector<Core::Pointer<IAttribute>> GetAttributes() const override {
			return m_attributes;
		}

		std::vector<Core::Pointer<IAttribute>> GetAttributes(Core::Guid& iid) const override {
			if (m_invalid_cache)
				const_cast<Node*>(this)->CacheAttribute(iid);
			auto it = m_attributes_cache.find(iid);
			if (it == m_attributes_cache.end()) {
				if (it == m_attributes_cache.end())
					return std::vector < Core::Pointer<IAttribute> > {};
			}
			return it->second;
		}

		void RemoveAttribute(const Core::String& name) override {
			try {
				auto index = GetAttributeIndex(name);
				RemoveAttribute(index);
			}
			catch (...) {
			}
		}

		void RemoveAttribute(std::uint32_t index) override {

			auto attribute = m_attributes.at(index);
			m_attributes.erase(m_attributes.begin() + index);

			//	remove from name cache
			m_name_cache.erase(attribute->GetName());

			//	remove from attributes cache
			//	get all cached interfaces for current index
			auto& interfaces = m_interface_map.find(index)->second;
			for (auto& iid : interfaces) {
				//	get all attributes that support curent interface
				auto& objects = m_attributes_cache[iid];
				//	try to find removing attribute in the attributes cache
				auto it = std::find(objects.begin(), objects.end(), attribute);
				if (it == objects.end())
					continue;
				//	if found remove
				objects.erase(it);
			}

			//	remove from interface map
			m_interface_map.erase(m_interface_map.find(index));

			attribute->SetOwner(nullptr);
		}

		void RemoveAttribute(Core::Pointer<IAttribute> value) override {
			auto index = GetAttributeIndex(value->GetName());
			RemoveAttribute(index);
		}

		bool HasAttribute(Core::Pointer<IAttribute> value) override {
			auto it = std::find(m_attributes.begin(), m_attributes.end(), value);
			return it != m_attributes.end();
		}

		NodeState GetState() const override {
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
			
			std::uint32_t count = (std::uint32_t)m_attributes.size();
			buffer.WriteUnsigned32(count);
			for (auto& value : m_attributes) {
				auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(value, Core::IID_ISerializable);
				serializable->Serialize(buffer);
			}

			//	save children
			count = (std::uint32_t)m_children.size();
			buffer.WriteUnsigned32(count);
			for (auto& node : m_children) {
				auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(node, Core::IID_ISerializable);
				serializable->Serialize(buffer);
			}
		}

		void Deserialize(Core::Buffer& buffer) override {

			std::uint32_t count = buffer.ReadUnsigned32();
			m_attributes.resize(count);
			for (auto& value : m_attributes) {
				Core::Guid clsid;
				buffer.ReadPod(clsid);
				if (clsid != SceneModule::CLSID_Attribute) {
					throw System::Error::SystemException("Unexpected CLSID");
				}
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				serializable->Deserialize(buffer);
				value = serializable;
				value->SetOwner(this);
			}

			//	save children
			count = buffer.ReadUnsigned32();
			m_children.resize(count);
			for (auto& node : m_children) {
				Core::Guid clsid;
				buffer.ReadPod(clsid);
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				serializable->Deserialize(buffer);
				node = serializable;
				node->SetParent(this);
			}
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		//NodeState m_state{ NodeState::Inactive };
		//std::uint64_t m_id{ 0 };
		INode* m_parent{ nullptr };
		std::vector<Core::Pointer<INode>> m_children;
		std::map<Core::String, std::uint32_t> m_name_cache;
		std::vector< Core::Pointer < IAttribute >> m_attributes;
		IScene* m_scene_graph{ nullptr };
		std::atomic<int> m_delete_count;
		bool m_invalid_cache{ false };
		std::map<Core::Guid, std::vector<Core::Pointer<IAttribute>>> m_attributes_cache;
		std::map<std::uint32_t, std::vector<Core::Guid>> m_interface_map;
	};

	PUNK_REGISTER_CREATOR(CLSID_Node, (System::CreateInstance<Node, INode>));

}
PUNK_ENGINE_END
