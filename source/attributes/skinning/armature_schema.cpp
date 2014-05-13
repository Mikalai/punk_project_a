#include "armature_schema.h"
#include "bone.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	ArmatureSchema::~ArmatureSchema() {
		while (!m_bones.empty()) {
			DestroyBone(m_bones.back());
			m_bones.pop_back();
		}
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
