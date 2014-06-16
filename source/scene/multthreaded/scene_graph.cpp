#include <core/ifactory.h>
#include <string/module.h>
#include "scene_graph.h"
#include "node.h"

PUNK_ENGINE_BEGIN
namespace Scene
{
	void SceneGraph::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;
		if (type == IID_ISceneGraph ||
			type == Core::IID_IObject) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

    void SceneGraph::Lock() {
        m_lock.Lock();
    }

    void SceneGraph::Unlock() {
        m_lock.Unlock();
    }

    SceneGraph::~SceneGraph() {
        Core::DestroyObject(m_root);
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
            Core::DestroyObject(m_root);
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
        ISceneGraphUniquePtr scene{new SceneGraph, Core::DestroyObject};
		INode* node{ nullptr };
		Core::GetFactory()->CreateInstance(IID_INode, (void**)&node);
		node->SetSceneGraph(scene.get());
		scene->SetSourcePath(path);
        node->SetAttribute(new Attribute<Core::String>(L"Name", L"Root"));
        node->SetAttribute(new Attribute<Core::String>(L"Type", L"FileProxy"));
        node->SetAttribute(new Attribute<Core::String>(L"Filename", file));        
        return scene;
    }

    void CreateScene(void** object) {
		if (!object)
			return;
		*object = (void*)(new SceneGraph);
    }

	PUNK_REGISTER_CREATOR(IID_ISceneGraph, CreateScene);

}
PUNK_ENGINE_END
