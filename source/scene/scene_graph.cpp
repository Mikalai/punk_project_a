#include <string/module.h>
#include "scene_graph.h"
#include "node.h"

PUNK_ENGINE_BEGIN
namespace Scene
{
    void SceneGraph::Lock() {
        m_lock.Lock();
    }

    void SceneGraph::Unlock() {
        m_lock.Unlock();
    }

    SceneGraph::~SceneGraph() {
        delete m_root;
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
            delete m_root;
        m_root = node;
    }

    extern "C" PUNK_ENGINE_API ISceneGraphUniquePtr CreateSceneFromFile(const Core::String& fullpath) {
        ISceneGraphUniquePtr scene{new SceneGraph, DestroyScene};
        Node* node = new Node(nullptr);
        node->SetAttribute(new Attribute<Core::String>(L"Name", L"Root"));
        node->SetAttribute(new Attribute<Core::String>(L"Type", L"FileProxy"));
        node->SetAttribute(new Attribute<Core::String>(L"Filename", fullpath));
        scene->SetRoot(node);
        return scene;
    }

    extern "C" PUNK_ENGINE_API ISceneGraphUniquePtr CreateScene() {
        ISceneGraphUniquePtr scene{new SceneGraph, DestroyScene};
        return scene;
    }

    extern "C" PUNK_ENGINE_API void DestroyScene(ISceneGraph* graph) {
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
