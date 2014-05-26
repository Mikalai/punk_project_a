#include <core/ifactory.h>
#include <attributes/stubs/module.h>
#include <string/module.h>
#include "iscene_observer.h"
#include "scene_graph.h"
#include "node.h"

PUNK_ENGINE_BEGIN
namespace SceneModule
{
	void Scene::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;
		if (type == IID_IScene ||
			type == Core::IID_IObject) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

    void Scene::Lock() {
        m_lock.Lock();
    }

    void Scene::Unlock() {
        m_lock.Unlock();
    }

    Scene::~Scene() {
        Core::DestroyObject(m_root);
        m_root = nullptr;
    }

    INode* Scene::GetRoot() {
        return m_root;
    }

    const INode* Scene::GetRoot() const {
        return m_root;
    }

    void Scene::SetRoot(INode* node) {
        if (m_root)
            Core::DestroyObject(m_root);
        m_root = node;
    }

	INode* Scene::ReleaseRoot() {
		auto result = m_root;
		m_root = nullptr;
		return result;
	}

	void Scene::AddObserver(ISceneObserver* observer) {
		auto it = m_observers.find(observer);
		if (it == m_observers.end()) {
			m_observers.insert(observer);
			observer->SetScene(this);
		}
	}

	void Scene::RemoveObserver(ISceneObserver* observer) {
		m_observers.erase(observer);
	}


    void Scene::OnNodeAdded(INode* parent, INode* child) {
		std::for_each(m_observers.begin(), m_observers.end(), [&parent, &child](ISceneObserver* o) {
			o->OnNodeAdded(parent, child);
		});
    }

    void Scene::OnNodeRemoved(INode* parent, INode* child) {
		std::for_each(m_observers.begin(), m_observers.end(), [&parent, &child](ISceneObserver* o) {
			o->OnNodeRemoved(parent, child);
		});
    }

	void Scene::OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) {
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &old_attribute, new_attribute](ISceneObserver* o) {
			o->OnAttributeUpdated(node, old_attribute, new_attribute);
		});
	}

	void Scene::OnAttributeAdded(INode* node, IAttribute* attribute) {
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &attribute](ISceneObserver* o) {
			o->OnAttributeAdded(node, attribute);
		});
	}

	void Scene::OnAttributeRemoved(INode* node, IAttribute* attribute) {
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &attribute](ISceneObserver* o) {
			o->OnAttributeRemoved(node, attribute);
		});
	}

	void Scene::SetSourcePath(const Core::String& path) {
		m_source_path = path;
	}

	const Core::String Scene::GetSourcePath() const {
		return m_source_path;
	}

	extern PUNK_ENGINE_API ISceneGraphUniquePtr CreateSceneFromFile(const Core::String& path, const Core::String& file) {
		ISceneGraphUniquePtr scene{ new Scene, Core::DestroyObject };
		INode* node{ nullptr };
		Core::GetFactory()->CreateInstance(IID_INode, (void**)&node);
		node->SetSceneGraph(scene.get());
		scene->SetSourcePath(path);	
		{
			Attributes::IFileStub* stub = nullptr;
			Core::GetFactory()->CreateInstance(Attributes::IID_IFileStub, (void**)&stub);
			stub->SetFilename(file);
			node->SetAttribute(new Attribute<Attributes::IFileStub>(L"Filename", stub));
		}
        return scene;
    }

    void CreateScene(void** object) {
		if (!object)
			return;
		*object = (void*)(new Scene);
    }

	PUNK_REGISTER_CREATOR(IID_IScene, CreateScene);

}
PUNK_ENGINE_END
