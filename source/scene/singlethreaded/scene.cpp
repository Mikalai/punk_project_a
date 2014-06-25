#include <system/factory/module.h>
#include <attributes/stubs/module.h>
#include <string/module.h>
#include "iscene_observer.h"
#include "scene.h"
#include "node.h"

PUNK_ENGINE_BEGIN
namespace SceneModule
{

	Scene::Scene() {
        LOG_FUNCTION_SCOPE
        m_root = System::CreateInstancePtr<INode>(IID_INode);
		m_root->SetScene(this);
	}

	Scene::~Scene() {
        LOG_FUNCTION_SCOPE
	}

	void Scene::QueryInterface(const Core::Guid& type, void** object) {
        LOG_FUNCTION_SCOPE
		Core::QueryInterface(this, type, object, { IID_IScene, Core::IID_IObject });
	}

    void Scene::Lock() {
        LOG_FUNCTION_SCOPE
        m_lock.Lock();
    }

    void Scene::Unlock() {
        LOG_FUNCTION_SCOPE
        m_lock.Unlock();
    }    

    INode* Scene::GetRoot() {
        LOG_FUNCTION_SCOPE
        return m_root.get();
    }

    const INode* Scene::GetRoot() const {
        LOG_FUNCTION_SCOPE
        return m_root.get();
    }

    void Scene::SetRoot(INode* node) {
        LOG_FUNCTION_SCOPE
        node->AddRef();
        if (m_root.get()) {
            OnNodeRemoved(nullptr, m_root.get());
		}		        
        m_root.reset(node);
		m_root->SetScene(this);
        OnNodeAdded(nullptr, m_root.get());
    }

	INode* Scene::ReleaseRoot() {
        LOG_FUNCTION_SCOPE
        return m_root.release();
	}

	void Scene::AddObserver(IObserver* observer) {		
        LOG_FUNCTION_SCOPE
		auto it = m_observers.find(observer);
		if (it == m_observers.end()) {
			observer->AddRef();
			m_observers.insert(observer);
			observer->SetScene(this);
		}
	}

	void Scene::RemoveObserver(IObserver* observer) {
        LOG_FUNCTION_SCOPE
		auto it = m_observers.find(observer);
		if (it != m_observers.end()) {
			m_observers.erase(observer);
			observer->Release();
		}
	}


    void Scene::OnNodeAdded(INode* parent, INode* child) {
        LOG_FUNCTION_SCOPE
		std::for_each(m_observers.begin(), m_observers.end(), [&parent, &child](IObserver* o) {
			o->OnNodeAdded(parent, child);
		});
    }

    void Scene::OnNodeRemoved(INode* parent, INode* child) {
        LOG_FUNCTION_SCOPE
		std::for_each(m_observers.begin(), m_observers.end(), [&parent, &child](IObserver* o) {
			o->OnNodeRemoved(parent, child);
		});
    }

	void Scene::OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) {
        LOG_FUNCTION_SCOPE
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &old_attribute, new_attribute](IObserver* o) {
			o->OnAttributeUpdated(node, old_attribute, new_attribute);
		});
	}

	void Scene::OnAttributeAdded(INode* node, IAttribute* attribute) {
        LOG_FUNCTION_SCOPE
		node->AddRef();
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &attribute](IObserver* o) {			
			o->OnAttributeAdded(node, attribute);
		});
		node->Release();
	}

	void Scene::OnAttributeRemoved(INode* node, IAttribute* attribute) {
        LOG_FUNCTION_SCOPE
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &attribute](IObserver* o) {
			o->OnAttributeRemoved(node, attribute);
		});
	}

	void Scene::SetSourcePath(const Core::String& path) {
        LOG_FUNCTION_SCOPE
		m_source_path = path;
	}

	const Core::String Scene::GetSourcePath() const {
        LOG_FUNCTION_SCOPE
		return m_source_path;
	}

	extern PUNK_ENGINE_API ISceneGraphUniquePtr CreateSceneFromFile(const Core::String& path, const Core::String& file) {
        LOG_FUNCTION_SCOPE
		ISceneGraphUniquePtr scene{ new Scene, Core::DestroyObject };
        auto node = System::CreateInstancePtr<INode>(IID_INode);
		node->SetScene(scene.get());
		scene->SetSourcePath(path);	
		{
            auto stub = System::CreateInstancePtr<Attributes::IFileStub>(Attributes::IID_IFileStub);
			stub->SetFilename(file);
            node->SetAttribute(new Attribute<Attributes::IFileStub>(L"Filename", stub.get()));
		}
        return scene;
    }

	PUNK_REGISTER_CREATOR(IID_IScene, (System::CreateInstance<Scene, IScene>));

}
PUNK_ENGINE_END
