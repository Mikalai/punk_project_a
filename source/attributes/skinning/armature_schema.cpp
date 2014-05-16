#include "armature_schema.h"
#include "bone.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	Core::Rtti ArmatureSchemaType{ "Punk.Engine.Attributes.ArmatureSchema", typeid(ArmatureSchema).hash_code(), { Core::IObject::Type() } };

	Core::Rtti* ArmatureSchema::Type() {
		return &ArmatureSchemaType;
	}

	ArmatureSchema::~ArmatureSchema() {
		while (!m_bones.empty()) {
			DestroyBone(m_bones.back());
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

	extern PUNK_ENGINE_API IArmatureSchemaUniquePtr CreateArmatureSchema() {
		return IArmatureSchemaUniquePtr{ new ArmatureSchema, DestroyArmatureSchema };
	}

	extern PUNK_ENGINE_API void DestroyArmatureSchema(IArmatureSchema* value) {
		ArmatureSchema* v = dynamic_cast<ArmatureSchema*>(value);
		delete v;
	}
}
PUNK_ENGINE_END
