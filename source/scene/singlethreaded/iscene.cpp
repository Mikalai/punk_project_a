#include <system/factory/module.h>
#include <attributes/stubs/module.h>
#include <string/module.h>
#include <core/iserializable.h>
#include <set>
#include <system/concurrency/thread_mutex.h>
#include <core/object.h>
#include "inode.h"
#include "iscene_observer.h"
#include "iscene.h"

PUNK_ENGINE_BEGIN
namespace SceneModule
{
	class PUNK_ENGINE_LOCAL Scene : public IScene, Core::ISerializable {
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
			if (!object)
				return;
			*object = nullptr;
			if (type == Core::IID_IObject) {
				*object = (IScene*)this;
				AddRef();
			}
			else if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
			else if (type == IID_IScene) {
				*object = (IScene*)this;
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

		void SetName(const Core::String& value) override {
			m_name = value;
		}
		const Core::String& GetName() const override {
			return m_name;
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			buffer.WriteBuffer(CLSID_Scene.ToPointer(), sizeof(CLSID_Scene));
			buffer.WriteString(m_name);
			auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(m_root, Core::IID_ISerializable);
			bool flag = serializable.get() != nullptr;
			buffer.WriteBoolean(flag);
			if (flag) {
				serializable->Serialize(buffer);
			}
			else {
				System::GetDefaultLogger()->Warning("Root node is not serializable");
			}
		}

		void Deserialize(Core::Buffer& buffer) override {
			m_name = buffer.ReadString();
			bool flag = buffer.ReadBoolean();
			if (flag) {
				Core::Guid clsid;
				buffer.ReadBuffer(clsid.ToPointer(), sizeof(clsid));
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				if (serializable) {
					serializable->Deserialize(buffer);
					m_root = Core::QueryInterfacePtr<INode>(serializable, IID_INode);
				}
				else
					System::GetDefaultLogger()->Error("No serializable object found in buffer");
			}
			else {
				System::GetDefaultLogger()->Warning("No root node found");
			}
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_name;
		std::set<Core::Pointer<IObserver>> m_observers;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<INode>> m_on_added_actions;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<INode>> m_on_removed_action;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<IAttribute>> m_on_attribute_added;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<IAttribute>, Core::Pointer<IAttribute>> m_on_attribute_updated;
		Core::ActionSlot<Core::Pointer<INode>, Core::Pointer<IAttribute>> m_on_attribute_removed;
		System::ThreadMutex m_lock;
		Core::Pointer<INode> m_root{ nullptr, Core::DestroyObject };
	};				    
    
	PUNK_REGISTER_CREATOR(CLSID_Scene, (System::CreateInstance<Scene, IScene>));

}
PUNK_ENGINE_END
