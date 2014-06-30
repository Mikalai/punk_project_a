#include <system/factory/module.h>
#include <attributes/stubs/module.h>
#include <string/module.h>
#include <set>
#include <system/concurrency/thread_mutex.h>
#include <core/object.h>
#include "inode.h"
#include "iscene_observer.h"
#include "iscene.h"

PUNK_ENGINE_BEGIN
namespace SceneModule
{
	class PUNK_ENGINE_LOCAL Scene : public IScene {
	public:
		Scene();
		virtual ~Scene();
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IScene
		void Lock() override;
		void Unlock() override;
		Core::Pointer<INode> GetRoot() override;
		const Core::Pointer<INode> GetRoot() const override;
		void SetRoot(Core::Pointer<INode> node) override;
		INode* ReleaseRoot() override;
		void AddObserver(Core::Pointer<IObserver> observer) override;
		void RemoveObserver(Core::Pointer<IObserver> observer) override;
		void OnNodeAdded(INode* parent, INode* child) override;
		void OnNodeRemoved(INode* parent, INode* child) override;
		void OnAttributeAdded(INode* node, IAttribute* attribute) override;
		void OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) override;
		void OnAttributeRemoved(INode* node, IAttribute* attribute) override;
		void SetSourcePath(const Core::String& path) override;
		const Core::String GetSourcePath() const override;
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::set<Core::Pointer<IObserver>> m_observers;
		Core::ActionSlot<INode*, INode*> m_on_added_actions;
		Core::ActionSlot<INode*, INode*> m_on_removed_action;
		Core::ActionSlot<INode*, IAttribute*> m_on_attribute_added;
		Core::ActionSlot<INode*, IAttribute*, IAttribute*> m_on_attribute_updated;
		Core::ActionSlot<INode*, IAttribute*> m_on_attribute_removed;
		Core::String m_source_path;
		System::ThreadMutex m_lock;
		Core::Pointer<INode> m_root{ nullptr, Core::DestroyObject };
	};

	void Scene::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IScene });
	}

	std::uint32_t Scene::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Scene::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

	Scene::Scene() {
		LOG_FUNCTION_SCOPE;
        m_root = System::CreateInstancePtr<INode>(IID_INode);
		m_root->SetScene(this);
	}

	Scene::~Scene() {
		LOG_FUNCTION_SCOPE;
	}

    void Scene::Lock() {
		LOG_FUNCTION_SCOPE;
        m_lock.Lock();
    }

    void Scene::Unlock() {
		LOG_FUNCTION_SCOPE;
        m_lock.Unlock();
    }    

    Core::Pointer<INode> Scene::GetRoot() {
		LOG_FUNCTION_SCOPE;
		return m_root;
    }

    const Core::Pointer<INode> Scene::GetRoot() const {
		LOG_FUNCTION_SCOPE;
		return m_root;
    }

    void Scene::SetRoot(Core::Pointer<INode> node) {
		LOG_FUNCTION_SCOPE;
        node->AddRef();
        if (m_root.get()) {
            OnNodeRemoved(nullptr, m_root.get());
		}		        
		m_root = node;
		m_root->SetScene(this);
        OnNodeAdded(nullptr, m_root.get());
    }

	INode* Scene::ReleaseRoot() {
		LOG_FUNCTION_SCOPE;
        return m_root.release();
	}

	void Scene::AddObserver(Core::Pointer<IObserver> observer) {		
		LOG_FUNCTION_SCOPE;
		auto it = m_observers.find(observer);
		if (it == m_observers.end()) {
			observer->AddRef();
			m_observers.insert(observer);
			observer->SetScene(this);
		}
	}

	void Scene::RemoveObserver(Core::Pointer<IObserver> observer) {
		LOG_FUNCTION_SCOPE;
		auto it = m_observers.find(observer);
		if (it != m_observers.end()) {
			m_observers.erase(observer);
			observer->Release();
		}
	}


    void Scene::OnNodeAdded(INode* parent, INode* child) {
		LOG_FUNCTION_SCOPE;
		std::for_each(m_observers.begin(), m_observers.end(), [&parent, &child](Core::Pointer<IObserver> o) {
			o->OnNodeAdded(parent, child);
		});
    }

    void Scene::OnNodeRemoved(INode* parent, INode* child) {
		LOG_FUNCTION_SCOPE;
		std::for_each(m_observers.begin(), m_observers.end(), [&parent, &child](Core::Pointer<IObserver> o) {
			o->OnNodeRemoved(parent, child);
		});
    }

	void Scene::OnAttributeUpdated(INode* node, IAttribute* old_attribute, IAttribute* new_attribute) {
		LOG_FUNCTION_SCOPE;
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &old_attribute, &new_attribute](Core::Pointer<IObserver> o) {
			o->OnAttributeUpdated(node, old_attribute, new_attribute);
		});
	}

	void Scene::OnAttributeAdded(INode* node, IAttribute* attribute) {
		LOG_FUNCTION_SCOPE;
		node->AddRef();
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &attribute](Core::Pointer<IObserver> o) {			
			o->OnAttributeAdded(node, attribute);
		});
		node->Release();
	}

	void Scene::OnAttributeRemoved(INode* node, IAttribute* attribute) {
		LOG_FUNCTION_SCOPE;
		std::for_each(m_observers.begin(), m_observers.end(), [&node, &attribute](Core::Pointer<IObserver> o) {
			o->OnAttributeRemoved(node, attribute);
		});
	}

	void Scene::SetSourcePath(const Core::String& path) {
		LOG_FUNCTION_SCOPE;
		m_source_path = path;
	}

	const Core::String Scene::GetSourcePath() const {
		LOG_FUNCTION_SCOPE;
		return m_source_path;
	}

	extern PUNK_ENGINE_API ISceneGraphPointer CreateSceneFromFile(const Core::String& path, const Core::String& file) {
		LOG_FUNCTION_SCOPE;
		ISceneGraphPointer scene{ new Scene, Core::DestroyObject };
        auto node = System::CreateInstancePtr<INode>(IID_INode);
		node->SetScene(scene.get());
		scene->SetSourcePath(path);	
		{
            auto stub = System::CreateInstancePtr<Attributes::IFileStub>(Attributes::IID_IFileStub);
			stub->SetFilename(file);
            node->SetAttribute(new Attribute<Attributes::IFileStub>(L"Filename", stub));
		}
        return scene;
    }

	PUNK_REGISTER_CREATOR(IID_IScene, (System::CreateInstance<Scene, IScene>));

}
PUNK_ENGINE_END
