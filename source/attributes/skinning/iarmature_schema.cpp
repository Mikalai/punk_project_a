#include <config.h>
#include <system/factory/module.h>
#include <core/iserializable.h>
#include <string/buffer.h>
#include <string/module.h>
#include "iarmature_schema.h"
#include "ibone.h"

PUNK_ENGINE_BEGIN
namespace Attributes {
	
	class PUNK_ENGINE_LOCAL ArmatureSchema : public IArmatureSchema, public Core::ISerializable {
	public:
		virtual ~ArmatureSchema() {			
		}
		
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;

			*object = nullptr;
			if (Core::IID_IObject == type) {
				*object = (IArmatureSchema*)this;
				AddRef();
			}
			else if (Core::IID_ISerializable == type) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
			else if (IID_IArmatureSchema == type) {
				*object = (IArmatureSchema*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}


		//	IArmatureSchema
		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String& GetName() const override {
			return m_name;
		}		

		std::uint32_t GetBonesCount() const override {
			return (std::uint32_t)m_bones.size();
		}

		Core::Pointer<IBone> GetBone(std::uint32_t index) override {
			return m_bones.at(index);
		}

		const Core::Pointer<IBone> GetBone(std::uint32_t index) const override {
			return m_bones.at(index);
		}

		std::uint32_t GetRootBonesCount() const override {
			return (std::uint32_t)m_root.size();
		}

		Core::Pointer<IBone> GetRootBone(int root_index) override {
			return m_bones.at(m_root.at(root_index));
		}

		const Core::Pointer<IBone> GetRootBone(int root_index) const override {
			return m_bones.at(m_root.at(root_index));
		}

		int GetBoneIndex(const Core::String& name) const override {
			for (size_t i = 0; i < m_bones.size(); ++i) {
				if (m_bones[i]->GetName() == name)
					return (int)i;
			}
			return -1;
		}

		void AddBone(Core::Pointer<IBone> value) override {
			auto index = value->GetIndex();
			if (m_bones.size() <= index)
				m_bones.resize(index + 1);
			m_bones[index] = value;
			if (!value->HasParent())
				m_root.push_back(index);
			else
				m_bones.at(value->GetParent())->AddChild(index);
		}

		std::uint32_t GetSupportedActionsCount() const override {
			return (std::uint32_t)m_supported_actions.size();
		}

		const Core::String& GetSupportedAction(std::uint32_t index) const override {
			return m_supported_actions.at(index);
		}

		void AddSupportedAction(const Core::String& name) override {
			m_supported_actions.push_back(name);
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) {
			buffer.WriteBuffer(CLSID_ArmatureSchema.ToPointer(), sizeof(CLSID_ArmatureSchema));
			buffer.WriteString(m_name);
			std::uint32_t count = (std::uint32_t)m_supported_actions.size();
			buffer.WriteUnsigned32(count);
			for (std::uint32_t i = 0; i < count; ++i) {
				buffer.WriteString(m_supported_actions[i]);
			}
			count = (std::uint32_t)m_root.size();
			buffer.WriteUnsigned32(count);
			buffer.WriteBuffer(m_root.data(), sizeof(std::uint32_t)*count);
			count = (std::uint32_t)m_bones.size();
			buffer.WriteUnsigned32(count);
			for (std::uint32_t i = 0; i < count; ++i) {
				auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(m_bones[i], Core::IID_ISerializable);
				bool flag = serializable.get() != nullptr;
				buffer.WriteBoolean(flag);
				if (flag)
					serializable->Serialize(buffer);
			}
		}

		void Deserialize(Core::Buffer& buffer) {
			m_name = buffer.ReadString();
			std::uint32_t count = buffer.ReadUnsigned32();
			m_supported_actions.resize(count);
			for (std::uint32_t i = 0; i < count; ++i) {
				m_supported_actions[i] = buffer.ReadString();
			}
			count = buffer.ReadUnsigned32();
			m_root.resize(count);
			buffer.ReadBuffer(m_root.data(), sizeof(std::uint32_t)*count);
			count = buffer.ReadUnsigned32();
			m_bones.resize(count);
			for (std::uint32_t i = 0; i < count; ++i) {
				Core::Guid clsid;
				bool flag = buffer.ReadBoolean();
				if (flag) {
					buffer.ReadBuffer(clsid.ToPointer(), sizeof(clsid));
					auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
					serializable->Deserialize(buffer);
					m_bones[i] = Core::QueryInterfacePtr<IBone>(serializable, IID_IBone);
				}
			}
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_name;
		std::vector<Core::String> m_supported_actions;
		std::vector<std::uint32_t> m_root;
		std::vector<Core::Pointer<IBone>> m_bones;
	};	

	PUNK_REGISTER_CREATOR(CLSID_ArmatureSchema, (System::CreateInstance<ArmatureSchema, IArmatureSchema>));
}
PUNK_ENGINE_END
