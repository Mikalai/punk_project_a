#include <config.h>
#include <core/ifactory.h>
#include <string/string.h>
#include "iarmature_schema.h"
#include "ibone.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class IBone;
	class PUNK_ENGINE_LOCAL ArmatureSchema : public IArmatureSchema {
	public:
		virtual ~ArmatureSchema();
		
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IArmatureSchema
		std::uint32_t GetBonesCount() const override;
		IBone* GetBone(std::uint32_t index) override;
		const IBone* GetBone(std::uint32_t index) const override;
		std::uint32_t GetRootBonesCount() const override;
		IBone* GetRootBone(int root_index) override;
		const IBone* GetRootBone(int root_index) const override;
		int GetBoneIndex(const Core::String& name) override;
		void AddBone(IBone* value) override;
		std::uint32_t GetSupportedActionsCount() const override;
		const Core::String& GetSupportedAction(std::uint32_t index) const override;
		void AddSupportedAction(const Core::String& name) override;
	private:
		std::vector<IBone*> m_bones;
		std::vector<std::uint32_t> m_root;
		std::vector<Core::String> m_supported_actions;
		std::atomic<std::uint32_t> m_ref_count{ 1 };
	};

	void ArmatureSchema::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IArmatureSchema });
	}

	std::uint32_t ArmatureSchema::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t ArmatureSchema::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}


	ArmatureSchema::~ArmatureSchema() {
		while (!m_bones.empty()) {
			m_bones.back()->Release();
			m_bones.pop_back();
		}
	}

	std::uint32_t ArmatureSchema::GetBonesCount() const {
		return m_bones.size();
	}

	IBone* ArmatureSchema::GetBone(std::uint32_t index) {
		return m_bones.at(index);
	}

	const IBone* ArmatureSchema::GetBone(std::uint32_t index) const {
		return m_bones.at(index);
	}

	std::uint32_t ArmatureSchema::GetRootBonesCount() const {
		return m_root.size();
	}

	IBone* ArmatureSchema::GetRootBone(int root_index) {
		return m_bones.at(m_root.at(root_index));
	}

	const IBone* ArmatureSchema::GetRootBone(int root_index) const {
		return m_bones.at(m_root.at(root_index));
	}

	int ArmatureSchema::GetBoneIndex(const Core::String& name) {
		for (size_t i = 0; i < m_bones.size(); ++i) {
			if (m_bones[i]->GetName() == name)
				return i;
		}
		return -1;
	}

	void ArmatureSchema::AddBone(IBone* value) {
		auto index = value->GetIndex();
		if (m_bones.size() <= index)
			m_bones.resize(index + 1);
		m_bones[index] = value;
		if (!value->HasParent())
			m_root.push_back(index);
		else
			m_bones.at(value->GetParent())->AddChild(index);
	}

	std::uint32_t ArmatureSchema::GetSupportedActionsCount() const {
		return m_supported_actions.size();
	}

	const Core::String& ArmatureSchema::GetSupportedAction(std::uint32_t index) const {
		return m_supported_actions.at(index);
	}

	void ArmatureSchema::AddSupportedAction(const Core::String& name) {
		m_supported_actions.push_back(name);
	}

	PUNK_REGISTER_CREATOR(IID_IArmatureSchema, (Core::CreateInstance<ArmatureSchema, IArmatureSchema>));
}
PUNK_ENGINE_END
