#include <algorithm>
#include <utility>
#include <iostream>
#include "iscene_graph.h"
#include <system/concurrency/module.h>
#include "node.h"

PUNK_ENGINE_BEGIN
namespace Scene {

    Node::Node(ISceneGraph *graph)
        : m_scene_graph{graph}
    {}

    Node::Node(INode *parent)
        : m_parent{parent} {
        if (m_parent) {
            m_parent->AddChild(this);
            m_scene_graph = m_parent->GetSceneGraph();
        }
    }

    Node::~Node() {
        while (!m_children.empty()) {
            delete m_children.back();
            m_children.pop_back();
        }

        for (auto pair : m_attributes) {
            delete pair.second;
        }
        m_attributes.clear();
    }

    void Node::SetAttribute(IAttribute *value) {
        auto key = std::pair<Core::String, std::uint64_t>(value->GetName(), value->GetTypeID());
        auto old = m_attributes[key];
		m_attributes[key] = value;
		if (old == nullptr)
			m_scene_graph->OnAttributeAdded(this, value);
		else {
			m_scene_graph->OnAttributeUpdated(this, old, value);
			delete old;
		}
    }

    IAttribute* Node::GetAttribute(const Core::String & name, std::uint64_t type) const
    {
        try {
            return m_attributes.at(std::pair<Core::String, std::uint64_t>(name, type));
        }
        catch(...) {
            return 0;
        }
    }

    void Node::RemoveAttribute(const Core::String &name, std::uint64_t type) {
        try {
            IAttribute* a = m_attributes.at(std::pair<Core::String, std::uint64_t>(name, type));
            delete a;
        }
        catch(...) {

        }
    }

    INode* Node::GetParent() {
        return m_parent;
    }

    const INode* Node::GetParent() const {
        return m_parent;
    }

    std::uint64_t Node::GetChildrenCount() const {
        return m_children.size();
    }

    INode* Node::GetChild(std::uint64_t index) {
        return m_children[index];
    }

    const INode* Node::GetChild(std::uint64_t index) const {
        return m_children[index];
    }

    void Node::AddChild(INode *child) {
        m_children.push_back(child);
		child->SetSceneGraph(GetSceneGraph());		
		GetSceneGraph()->OnNodeAdded(this, child);
    }

	void Node::SetSceneGraph(ISceneGraph* graph) {
		m_scene_graph = graph;
		for (auto child : m_children) {
			child->SetSceneGraph(graph);
		}
	}

    NodeState Node::GetState() const {
        return m_state;
    }

    void Node::SetState(NodeState value) {
        m_state = value;
    }

    void Node::RemoveChild(INode* child, bool depth) {
        auto it = std::find(m_children.begin(), m_children.end(), child);
        if (it != m_children.end()) {
            m_children.erase(it);
            delete child;
        }
        else if (depth) {
            for (auto c : m_children)
                c->RemoveChild(child, depth);
        }
    }

    INode* Node::FindChild(IAttribute* attribute, bool depth) {
        for (INode* child : m_children) {
            if (child->GetAttribute(attribute->GetName(), attribute->GetTypeID()))
                return child;
        }
        if (depth)
            for (INode* child : m_children) {
                INode* res = child->FindChild(attribute, depth);
                if (res)
                    return res;
            }
        return nullptr;
    }

    ISceneGraph* Node::GetSceneGraph() {
        return m_scene_graph;
    }

    void Node::AddRef() {
        ++m_ref_count;
    }

    void Node::Release() {
        --m_ref_count;
    }

    void Node::MarkToDelete() {
        --m_delete_count;
    }

    void Node::AskToDelete() {
        ++m_delete_count;
    }

    bool Node::CanDelete() {
        return m_delete_count == 0;
    }

    extern PUNK_ENGINE_API INodeUniquePtr CreateRootNode(ISceneGraph* graph) {
        INodeUniquePtr node{new Node{graph}, DestroyNode};
        return node;
    }

    extern PUNK_ENGINE_API INodeUniquePtr CreateNode(INode* parent) {
        INodeUniquePtr node{new Node{parent}, DestroyNode};
        return node;
    }

    extern PUNK_ENGINE_API void DestroyNode(INode* node) {
        Node* n = dynamic_cast<Node*>(node);
        delete n;
    }

}
PUNK_ENGINE_END

//    PUNK_OBJECT_REG(Node, "Scene.Node", PUNK_NODE, SaveNode, LoadNode, &System::CompoundObject::Info.Type);

//    void SaveNode(Core::Buffer* buffer, const Core::Object* object)
//    {
//        System::SaveCompoundObject(buffer, object);
//        const Node* node = Cast<const Node*>(object);
//        //  SceneGraph* m_graph - SKIP
//        System::Factory::Save(buffer, node->m_data);
//        System::SaveString(buffer, node->m_entity_name);
//        Math::SaveBoundingBox(buffer, node->m_bbox);
//        Math::SaveBoundingSphere(buffer, node->m_bsphere);
//        //  Loader::AsyncParserTask* m_task - SKIP
//        Math::SaveVector3f(buffer, node->m_local_position);
//        Math::SaveQuaternion(buffer, node->m_local_rotation);
//        Math::SaveVector3f(buffer, node->m_local_scale);
//        Math::SaveVector3f(buffer, node->m_global_position);
//        Math::SaveQuaternion(buffer, node->m_global_rotation);
//        Math::SaveVector3f(buffer, node->m_global_scale);
//        buffer->WriteBoolean(node->m_need_transform_update);
//    }

//    void LoadNode(Core::Buffer* buffer, Core::Object* object)
//    {
//        System::LoadCompoundObject(buffer, object);
//        Node* node = Cast<Node*>(object);
//        //  SceneGraph* m_graph - SKIP
//        node->m_data = System::Factory::Load(buffer);
//        System::LoadString(buffer, node->m_entity_name);
//        Math::LoadBoundingBox(buffer, node->m_bbox);
//        Math::LoadBoundingSphere(buffer, node->m_bsphere);
//        //  Loader::AsyncParserTask* m_task - SKIP
//        Math::LoadVector3f(buffer, node->m_local_position);
//        Math::LoadQuaternion(buffer, node->m_local_rotation);
//        Math::LoadVector3f(buffer, node->m_local_scale);
//        Math::LoadVector3f(buffer, node->m_global_position);
//        Math::LoadQuaternion(buffer, node->m_global_rotation);
//        Math::LoadVector3f(buffer, node->m_global_scale);
//        node->m_need_transform_update = buffer->ReadBoolean();
//    }

//    Node::Node()
//        : m_data(nullptr)
//        , m_task(nullptr)
//    {
//        Info.Add(this);
//    }

//    Node::~Node()
//    {
//        delete m_task;
//        Info.Remove(this);
//    }

//    Node* Node::Clone()
//    {
//        std::unique_ptr<Node> node{new Node};
//        node->Name(GetName());
//        node->SetBoundingBox(GetBoundingBox());
//        node->SetBoundingSphere(GetBoundingSphere());
//        node->SetData(GetData());
//        node->SetOwner(GetOwner());
//        CloneInternals(node.get());
//        return node.release();
//    }

//    void Node::CloneInternals(Node *dst)
//    {
//        for (auto o : m_children)
//        {
//            Node* n = As<Node*>(o);
//            if (n)
//                dst->Add(n->Clone());
//        }
//    }

//    void Node::SetData(Core::Object* value)
//    {
//        m_data = value;
//    }

//    SceneGraph* Node::Graph() const
//    {
//        return m_graph;
//    }

//    void Node::Graph(SceneGraph* graph)
//    {
//        m_graph = graph;
//    }

//    Core::Object* Node::GetData()
//    {
//        if (m_data == nullptr)
//        {
//            m_data = System::HasInstance<Core::Object>(m_entity_name);
//        }
//        return m_data;
//    }

//    Core::Object* Node::GetOrLoadData()
//    {
//        if (m_data)
//            return m_data;

//        if (!Task())
//        {
//            //  no data cached
//            if (m_data == nullptr)
//            {
//                //  try to find
//                m_data = System::HasInstance<Core::Object>(m_entity_name);
//                if (m_data) //  fond - ok - return
//                    return m_data;
//            }

//            //  if node has got no data and there was no task to load data, than try to load data into the node
//            auto name = EntityName();
//            Graph()->AsyncParser()->Add(Task(new Loader::AsyncParserTask(Loader::FindPath(name))));
//        }
//        else
//        {
//            //  node has got no data and we assigned loading task to the node
//            if (Task()->State() == Loader::AsyncParserTask::AsyncSuccess)
//            {
//                //  if loading complete succesfull, move object from task to node data
//                SetData(Task()->Release());
//                //  delete node task (now we have and object). If something will delete object from
//                //  the node, we will create it again, because the will not be any tasks assigned to
//                //  the node
//                Task(nullptr);
//            }
//            else if (Task()->State() == Loader::AsyncParserTask::AsyncFailed)
//            {
//                //  if loading failed to complete there is no reason to continue work.
//                //  TODO: Maybe it is possible to continue work, when failed to load
//                throw System::PunkException(L"Failed to load resource: " + Task()->Path());
//            }
//        }
//        return nullptr;
//    }

//    const Core::Object* Node::GetData() const
//    {
//        return m_data;
//    }

//    const Core::String Node::ToString() const
//    {
//        return Core::String("{0} ({1}); {2} ({3}); {4} ({5})").arg(m_local_position.ToString())
//                .arg(m_global_position.ToString()).arg(m_local_rotation.ToString())
//                .arg(m_global_rotation.ToString()).arg(m_local_scale.ToString())
//                .arg(m_global_scale.ToString());
//    }

//    bool Node::Remove(const Core::String& name, bool depth)
//    {
//        return System::CompoundObject::Remove(Find(name, depth), depth);
//    }

//    const Node* Node::Find(const Core::String& name, bool in_depth) const
//    {
//        for (Object* o : m_children)
//        {
//            Node* n = As<Node*>(o);
//            if (n && (n->GetName() == name))
//                return n;
//        }
//        if (in_depth)
//        {
//            for (Object* o : m_children)
//            {
//                Node* co = As<Node*>(o);
//                if (co)
//                {
//                    Node* res = co->Find(name, in_depth);
//                    if (res)
//                        return res;
//                }
//            }
//        }
//        return nullptr;
//    }

//    size_t Node::GetIndex(const Core::String& name) const
//    {
//        size_t index = 0;
//        for (const Object* o : m_children)
//        {
//            const Node* n = As<const Node*>(o);
//            if (n && (n->GetName() == name))
//                return index;
//            index++;
//        }
//        return -1;
//    }

//    Node* Node::Find(const Core::String& name, bool in_depth)
//    {
//        for (Object* o : m_children)
//        {
//            Node* node = As<Node*>(o);
//            if (node)
//            {
//                if (node->GetName() == name)
//                    return node;
//                if (in_depth)
//                {
//                    Node* n = node->Find(name, in_depth);
//                    if (n != nullptr)
//                        return n;
//                }
//            }
//        }
//        return nullptr;
//    }

//    std::vector<Node*> Node::FindAll(const Core::String& name, bool in_depth, bool strict_compare)
//    {
//        std::vector<Node*> res;
//        for (Object* o : m_children)
//        {
//            Node* n = As<Node*>(o);
//            if (strict_compare)
//            {
//                if (n && (n->GetName() == name))
//                {
//                    res.push_back(n);
//                }
//            }
//            else
//            {
//                if (n && (n->GetName().find(name) != Core::String::npos))
//                {
//                    res.push_back(n);
//                }
//            }
//            if (in_depth)
//            {
//                if (n)
//                {
//                    auto child_res = n->FindAll(name, in_depth, strict_compare);
//                    res.insert(res.end(), child_res.begin(), child_res.end());
//                }
//            }
//        }
//        return res;
//    }

//    Loader::AsyncParserTask* Node::Task() const
//    {
//        return m_task;
//    }

//    Loader::AsyncParserTask* Node::Task(Loader::AsyncParserTask* value)
//    {
//        if (m_task)
//            delete m_task;
//        return m_task = value;
//    }

//    void Node::LocalPosition(const Math::vec3& value)
//    {
//        m_local_position = value;
//        m_need_transform_update = true;
//    }

//    const Math::vec3& Node::LocalPosition() const
//    {
//        return m_local_position;
//    }

//    Math::vec3& Node::LocalPosition()
//    {
//        return m_local_position;
//    }

//    const Math::vec3& Node::GlobalPosition() const
//    {
//        return m_global_position;
//    }

//    Math::vec3& Node::GlobalPosition()
//    {
//        UpdateGlobalPosition();
//        return m_global_position;
//    }

//    void Node::UpdateGlobalPosition()
//    {
//        Node* parent = Cast<Node*>(GetOwner());
//        if (!parent)
//            m_global_position = m_local_position;
//        else
//            m_global_position = parent->GlobalPosition() + parent->GlobalRotation().Rotate(m_local_position);
//    }

//    void Node::LocalRotation(const Math::quat& value)
//    {
//        m_local_rotation = value;
//        m_need_transform_update = true;
//    }

//    const Math::quat& Node::LocalRotation() const
//    {
//        return m_local_rotation;
//    }

//    Math::quat& Node::LocalRotation()
//    {
//        return m_local_rotation;
//    }

//    const Math::quat& Node::GlobalRotation() const
//    {
//        return m_global_rotation;
//    }

//    Math::quat& Node::GlobalRotation()
//    {
//        UpdateGlobalRotation();
//        return m_global_rotation;
//    }

//    void Node::UpdateGlobalRotation()
//    {
//        Node* parent = (Node*)GetOwner();
//        if (!parent)
//            m_global_rotation = m_local_rotation;
//        else
//            m_global_rotation = parent->GlobalRotation()*m_local_rotation;
//    }

//    void Node::LocalScale(const Math::vec3& value)
//    {
//        m_local_scale = value;
//        m_need_transform_update = true;
//    }

//    const Math::vec3& Node::LocalScale() const
//    {
//        return m_local_scale;
//    }

//    Math::vec3& Node::LocalScale()
//    {
//        return m_local_scale;
//    }

//    const Math::vec3& Node::GlobalScale() const
//    {
//        return m_global_scale;
//    }

//    Math::vec3& Node::GlobalScale()
//    {
//        UpdateGlobalScale();
//        return m_global_scale;
//    }

//    void Node::UpdateGlobalScale()
//    {
//        Node* parent = (Node*)GetOwner();
//        if (!parent)
//            m_global_scale = m_local_scale;
//        else
//            m_global_scale = parent->GlobalScale().ComponentMult(m_local_scale);
//    }

//    const Math::mat4 Node::GetLocalMatrix() const
//    {
//        return Math::mat4::CreateTranslate(m_local_position)*Math::mat4::CreateFromQuaternion(m_local_rotation);
//    }

//    const Math::mat3 Node::GetLocalRotationMatrix() const
//    {
//        return Math::mat3::CreateFromQuaternion(m_local_rotation);
//    }

//    const Math::mat4 Node::GetGlobalMatrix() const
//    {
//        return Math::mat4::CreateTranslate(m_global_position)*Math::mat4::CreateFromQuaternion(m_global_rotation);
//    }

//    const Math::mat3 Node::GetGlobalRotationMatrix() const
//    {
//        return Math::mat3::CreateFromQuaternion(m_global_rotation);
//    }

//    const Math::vec3 Node::LocalTransform(const Math::vec3& value) const
//    {
//        return m_local_rotation.Rotate(value) + m_local_position;
//    }

//    const Math::vec3 Node::LocalInversedTransform(const Math::vec3& value) const
//    {
//        Math::quat q(m_local_rotation.Conjugated());
//        return q.Rotate(value - m_local_position);
//    }

//    const Math::vec3 Node::GlobalTransform(const Math::vec3& value) const
//    {
//        return m_global_rotation.Rotate(value) + m_global_position;
//    }

//    const Math::vec3 Node::GlobalInversedTransform(const Math::vec3& value) const
//    {
//        Math::quat q(m_global_rotation.Conjugated());
//        return q.Rotate(value - m_global_position);
//    }

//    void Node::EntityName(const Core::String& value)
//    {
//        m_entity_name = value;
//    }

//    const Core::String& Node::EntityName() const
//    {
//        return m_entity_name;
//    }

//    bool Node::NeedTransformUpdate() const
//    {
//        return m_need_transform_update;
//    }

//    void Node::UpdateGlobalTransform()
//    {
//        //  use const, because it is supposed that upper nodes already have valid transform
//        const Node* parent = (const Node*)GetOwner();
//        if (!parent)
//        {
//            m_global_position = m_local_position;
//            m_global_rotation = m_local_rotation;
//        }
//        else
//        {
//            m_global_position = parent->GlobalPosition() + parent->GlobalRotation().Rotate(m_local_position);
//            m_global_rotation = parent->GlobalRotation() * m_local_rotation;
//        }
//    }

//    void UpdateUpToDown(Node *node)
//    {
//        node->UpdateGlobalTransform();
//        for (Core::Object* o : *node)
//        {
//            if (o->GetType()->GetId() == PUNK_NODE)
//            {
//                Node* child = (Node*)o;
//                UpdateUpToDown(child);
//            }
//        }
//    }

//    void Node::Rotate(const Math::quat &q)
//    {
//        m_local_rotation = m_local_rotation * q;
//    }

//    void Node::Translate(const Math::vec3 &p)
//    {
//        m_local_position += p;
//    }
