#include <string/module.h>
#include "scene_graph.h"
#include "node.h"

PUNK_ENGINE_BEGIN
namespace Scene
{
	static Core::Rtti SceneGraphType{ "Scene.SceneGraph", typeid(SceneGraph).hash_code(), { Core::Object::Type() } };

	Core::Rtti* SceneGraph::Type() {
		return &SceneGraphType;
	}

    void SceneGraph::Lock() {
        m_lock.Lock();
    }

    void SceneGraph::Unlock() {
        m_lock.Unlock();
    }

    SceneGraph::~SceneGraph() {
        DestroyNode(m_root);
        m_root = nullptr;
    }

    INode* SceneGraph::GetRoot() {
        return m_root;
    }

    const INode* SceneGraph::GetRoot() const {
        return m_root;
    }

    void SceneGraph::SetRoot(INode* node) {
        if (m_root)
            DestroyNode(m_root);
        m_root = node;
    }

	INode* SceneGraph::ReleaseRoot() {
		auto result = m_root;
		m_root = nullptr;
		return result;
	}

    void SceneGraph::SubscribeOnNodeAdded(Core::ActionBase<INode*, INode*>* value) {
        m_on_added_actions.Add(value, true);
    }

    void SceneGraph::SubscribeOnNodeRemoved(Core::ActionBase<INode*, INode*>* value) {
        m_on_removed_action.Add(value, true);
    }

	void SceneGraph::SubscribeOnAttributeAdded(Core::ActionBase<INode*, IAttribute*>* value) {
		m_on_attribute_added.Add(value, true);
	}

	void SceneGraph::SubscribeOnAttributeUpdated(Core::ActionBase<INode*, IAttribute*, IAttribute*>* value) {
		m_on_attribute_updated.Add(value, true);
	}

	void SceneGraph::SubscribeOnAttributeRemoved(Core::ActionBase<INode*, IAttribute*>* value) {
		m_on_attribute_removed.Add(value, true);
	}


    void SceneGraph::OnNodeAdded(INode* parent, INode* child) {
        m_on_added_actions(parent, child);
    }

    void SceneGraph::OnNodeRemoved(INode* parent, INode* child) {
        m_on_removed_action(parent, child);
    }

	void SceneGraph::OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) {
		m_on_attribute_updated(node, old_attribute, new_attribute);
	}

	void SceneGraph::OnAttributeAdded(INode* node, IAttribute* attribute) {
		m_on_attribute_added(node, attribute);
	}

	void SceneGraph::OnAttributeRemoved(INode* node, IAttribute* attribute) {
		m_on_attribute_removed(node, attribute);
	}

	void SceneGraph::SetSourcePath(const Core::String& path) {
		m_source_path = path;
	}

	const Core::String SceneGraph::GetSourcePath() const {
		return m_source_path;
	}

    extern PUNK_ENGINE_API ISceneGraphUniquePtr CreateSceneFromFile(const Core::String& path, const Core::String& file) {
        ISceneGraphUniquePtr scene{new SceneGraph, DestroyScene};
        INodeUniquePtr node = CreateRootNode(scene.get());
		scene->SetSourcePath(path);
        node->SetAttribute(new Attribute<Core::String>(L"Name", L"Root"));
        node->SetAttribute(new Attribute<Core::String>(L"Type", L"FileProxy"));
        node->SetAttribute(new Attribute<Core::String>(L"Filename", file));
        scene->SetRoot(node.release());
        return scene;
    }

    extern PUNK_ENGINE_API ISceneGraphUniquePtr CreateScene() {
        ISceneGraphUniquePtr scene{new SceneGraph, DestroyScene};
        return scene;
    }

    extern PUNK_ENGINE_API void DestroyScene(ISceneGraph* graph) {
        delete graph;
    }



//    PUNK_OBJECT_REG(SceneGraph, "Scene.SceneGraph", PUNK_SCENE_GRAPH, SaveSceneGraph, LoadSceneGraph, &Node::Info.Type);

//    SceneGraph::SceneGraph()
//        : m_parser(new Loader::AsyncParser)
//	{
//        Info.Add(this);
//	}

//	SceneGraph::~SceneGraph()
//	{
//        delete m_parser;
//        Info.Remove(this);
//	}

//    const Core::String SceneGraph::ToString() const
//    {
//        std::wstringstream stream;
//        stream << L'[' << GetLocalIndex() << L' ' << Info.Type.GetName() << L']' << std::endl;
//        for (auto o : m_children)
//        {
//            stream << o->ToString() << std::endl;
//        }
//        return Core::String(stream.str());
//    }

//    Loader::AsyncParser* SceneGraph::AsyncParser()
//    {
//        return m_parser;
//    }

//    void SaveSceneGraph(Core::Buffer *buffer, const Core::Object *o)
//    {
//        SaveNode(buffer, o);
//    }

//    void LoadSceneGraph(Core::Buffer *buffer, Core::Object *o)
//    {
//        LoadNode(buffer, o);
//    }


//    void UpdateLight(Node* node, std::vector<Node*>& nodes)
//    {
//        if (!node)
//            return;
//        auto o = node->GetData();
//        if (o)
//        {
//            if (o->GetType()->IsDerived(&Attributes::Light::Info.Type))
//            {
//                nodes.push_back(node);
//            }
//        }

//        for (auto child : *node)
//        {
//            Node* n = Cast<Node*>(child);
//            UpdateLight(n, nodes);
//        }
//    }

//    void SceneGraph::UpdateLights()
//    {
//        UpdateLight(this, m_lights);
//    }

//    void SceneGraph::UpdateTransform()
//    {
//        UpdateUpToDown(this);
//    }

//    void SceneGraph::Update()
//    {
//        UpdateTransform();
//        UpdateLights();
//    }

//    Node* SceneGraph::GetNearestLight(const Math::vec3 &point) const
//    {
//        if (m_lights.empty())
//            return nullptr;
//        size_t best = 0;
//        for (size_t i = 1, max_i = m_lights.size(); i < max_i; ++i)
//        {
//            const auto& p1 = m_lights[i]->GlobalPosition();
//            const auto& p2 = m_lights[best]->GlobalPosition();
//            float a = (p1 - point).Length();
//            float b = (p2 - point).Length();
//            if (a < b)
//                best = i;
//        }
//        return m_lights[best];
//    }
}
PUNK_ENGINE_END
