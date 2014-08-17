#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <memory>
#include <system/logger/module.h>
#include <system/factory/module.h>
#include <core/iserializable.h>
#include <core/iclonable.h>
#include "inode.h"
#include "iattribute.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

    class PUNK_ENGINE_LOCAL Attribute : public IAttribute, public Core::ISerializable, public Core::IClonable
    {
    public:		

		~Attribute() {
			LOG_FUNCTION_SCOPE();
			SetOwner(nullptr);
			System::GetDefaultLogger()->Info("Destroy attribute " + m_name);
			while (!m_update_actions.empty()) {
				m_update_actions.back()->Release();
				m_update_actions.pop_back();
			}
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			LOG_FUNCTION_SCOPE();
			if (!object)
				return;

			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IAttribute*)this;
				AddRef();
			}
			else if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
			else if (type == IID_IAttribute) {
				*object = (IAttribute*)this;
				AddRef();
			}
			else if (type == Core::IID_IClonable) {
				*object = (Core::IClonable*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() {
			LOG_FUNCTION_SCOPE();
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() {
			LOG_FUNCTION_SCOPE();
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IAttribute		
		void Initialize(const Core::String& name, Core::Pointer<Core::IObject> value) override {
			LOG_FUNCTION_SCOPE();
			m_name = name;
			m_data = value;
		}

		INode* GetOwner() const override {
			LOG_FUNCTION_SCOPE();
			return m_owner;
		}

		void SetOwner(INode* value) {
			LOG_FUNCTION_SCOPE();
			if (m_owner == value)
				return; 
			auto attribute = Core::Pointer < IAttribute > {this, Core::DestroyObject};
			if (m_owner && m_owner->HasAttribute(attribute)) {
				m_owner->RemoveAttribute(attribute);
			}

			m_owner = value;
			if (m_owner && !m_owner->HasAttribute(attribute)) {
				m_owner->AddAttribute(attribute);
			}
		}

		inline const Core::String& GetName() const {
			LOG_FUNCTION_SCOPE();
			return m_name;
		}

		inline void SetName(const Core::String& value) {
			LOG_FUNCTION_SCOPE();
			if (m_owner) {
				m_owner->RemoveAttribute(Core::Pointer < IAttribute > {this, Core::DestroyObject});				
			}
			m_name = value;
			if (m_owner) {
				m_owner->AddAttribute(Core::Pointer<IAttribute>(this, Core::DestroyObject));
			}
		}

		inline Core::Pointer<Core::IObject> GetRawData() const {
			LOG_FUNCTION_SCOPE();
			return m_data;
		}

		inline void SetRawData(Core::Pointer<Core::IObject> value) {			
			LOG_FUNCTION_SCOPE();
			m_data = value;
			for (auto action : m_update_actions) {
				(*action)(Core::Pointer < IAttribute > {this, Core::DestroyObject});
			}
		}

		inline void OnUpdate(Core::ActionBase<Core::Pointer<IAttribute>>* action) {
			LOG_FUNCTION_SCOPE();
			action->AddRef();
			m_update_actions.push_back(action);
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			LOG_FUNCTION_SCOPE();
			buffer.WritePod(CLSID_Attribute);
			buffer.WriteString(m_name);
			auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(m_data, Core::IID_ISerializable);
			bool has_data = serializable.get() != nullptr;
			buffer.WriteBoolean(has_data);			
			if (has_data) {
				serializable->Serialize(buffer);
			}
		}

		void Deserialize(Core::Buffer& buffer) override {
			LOG_FUNCTION_SCOPE();
			m_name = buffer.ReadString();
			bool has_data = buffer.ReadBoolean();
			if (has_data) {
				Core::Guid clsid;
				buffer.ReadPod(clsid);
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				serializable->Deserialize(buffer);
			}
		}

		//	IClonable
		Core::Pointer<Core::IClonable> Clone() const override {
			LOG_FUNCTION_SCOPE();
			//	select name
			Core::String base_name = GetName();
			Core::String name = base_name;
			if (m_owner) {
				int i = 1;
				while (m_owner->HasAttribute(name)) {
					name = base_name + L"_" + Core::String::Convert(i);
				}
			}

			auto o = Core::Pointer < Core::IObject > {nullptr, Core::DestroyObject};
			{
				auto tmp = Core::QueryInterfacePtr<Core::IClonable>(GetRawData(), Core::IID_IClonable);
				if (tmp) {
					o = Core::QueryInterfacePtr<Core::IObject>(tmp->Clone(), Core::IID_IObject);
				}
			}
			std::unique_ptr<Attribute> clone{ new Attribute };
			clone->Initialize(name, o);
			clone->SetOwner(m_owner);
			return Core::Pointer<Core::IClonable>(clone.release(), Core::DestroyObject);
		}

    private:        
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		INode* m_owner = nullptr;
        Core::String m_name;
		Core::Pointer<Core::IObject> m_data{ nullptr, Core::DestroyObject };
		std::vector < Core::ActionBase<Core::Pointer<IAttribute>>*> m_update_actions;
    };	

	PUNK_REGISTER_CREATOR(CLSID_Attribute, (System::CreateInstance<Attribute, IAttribute>));
}
PUNK_ENGINE_END

#endif // ATTRIBUTE_H
