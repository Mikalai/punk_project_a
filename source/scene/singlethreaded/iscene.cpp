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
		Scene() {
			LOG_FUNCTION_SCOPE;
			m_root = System::CreateInstancePtr<INode>(CLSID_Node, IID_INode);
			m_root->SetScene(this);
		}

		virtual ~Scene() {
			LOG_FUNCTION_SCOPE;
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IScene });
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

		//	IScene
		void Lock() override {
			LOG_FUNCTION_SCOPE;
			m_lock.Lock();
		}

		void Unlock() override {
			LOG_FUNCTION_SCOPE;
			m_lock.Unlock();
		}

		Core::Pointer<INode> GetRoot() override {
			LOG_FUNCTION_SCOPE;
			return m_root;
		}

		const Core::Pointer<INode> GetRoot() const override {
			LOG_FUNCTION_SCOPE;
			return m_root;
		}

		void SetRoot(Core::Pointer<INode> node) override {
			LOG_FUNCTION_SCOPE;
			node->AddRef();
			if (m_root.get()) {
				OnNodeRemoved(Core::Pointer < INode > {nullptr, Core::DestroyObject}, m_root);
			}
			m_root = node;
			m_root->SetScene(this);
			OnNodeAdded(Core::Pointer < INode > {nullptr, Core::DestroyObject}, m_root);
		}

		void AddObserver(Core::Pointer<IObserver> observer) override {
			LOG_FUNCTION_SCOPE;
			auto it = m_observers.find(observer);
			if (it == m_observers.end()) {
				observer->AddRef();
				m_observers.insert(observer);
				observer->SetScene(this);
			}
		}

		void RemoveObserver(Core::Pointer<IObserver> observer) override {
			LOG_FUNCTION_SCOPE;
			auto it = m_observers.find(observer);
			if (it != m_observers.end()) {
				m_observers.erase(observer);
				observer->Release();
			}
		}
	
		void OnNodeAdded(Core::Pointer<INode> parent, Core::Pointer<INode> child) override {
			LOG_FUNCTION_SCOPE;
			std::for_each(m_observers.begin(), m_observers.end(), [&parent, &child](Core::Pointer<IObserver> o) {
				o->OnNodeAdded(parent, child);
			});
		}

		void OnNodeRemoved(Core::Pointer<INode> parent, Core::Pointer<INode> child) override {
			LOG_FUNCTION_SCOPE;
			std::for_each(m_observers.begin(), m_observers.end(), [&parent, &child](Core::Pointer<IObserver> o) {
				o->OnNodeRemoved(parent, child);
			});
		}

		void OnAttributeAdded(Core::Pointer<INode> node, Core::Pointer<IAttribute> attribute) override {
			LOG_FUNCTION_SCOPE;
			node->AddRef();
			std::for_each(m_observers.begin(), m_observers.end(), [&node, &attribute](Core::Pointer<IObserver> o) {
				o->OnAttributeAdded(node, attribute);
			});
			node->Release();
		}

		void OnAttributeUpdated(Core::Pointer<INode> node, Core::Pointer<IAttribute> old_attribute, Core::Pointer<IAttribute> new_attribute) override {
			LOG_FUNCTION_SCOPE;
			std::for_each(m_observers.begin(), m_observers.end(), [&node, &old_attribute, &new_attribute](Core::Pointer<IObserver> o) {
				o->OnAttributeUpdated(node, old_attribute, new_attribute);
			});
		}

		void OnAttributeRemoved(Core::Pointer<INode> node, Core::Pointer<IAttribute> attribute) override {
			LOG_FUNCTION_SCOPE;
			std::for_each(m_observers.begin(), m_observers.end(), [&node, &attribute](Core::Pointer<IObserver> o) {
				o->OnAttributeRemoved(node, attribute);
			});
		}
		
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::set<Core::Pointer<IObserver>> m_observers;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<INode>> m_on_added_actions;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<INode>> m_on_removed_action;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<IAttribute>> m_on_attribute_added;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<IAttribute>, Core::Pointer<IAttribute>> m_on_attribute_updated;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<IAttribute>> m_on_attribute_removed;
		Core::String m_source_path;
		System::ThreadMutex m_lock;
		Core::Pointer<INode> m_root{ nullptr, Core::DestroyObject };
	};				    
    
	PUNK_REGISTER_CREATOR(CLSID_Scene, (System::CreateInstance<Scene, IScene>));

}
PUNK_ENGINE_END
