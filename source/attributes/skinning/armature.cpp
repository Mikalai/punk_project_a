#include <algorithm>
#include <stack>
#include <memory>
#include <iostream>
#include <fstream>
#include <string/module.h>
#include "armature.h"
#include "iarmature_schema.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti ArmatureType{ L"Attributes.Armature", typeid(Armature).hash_code(), { Core::IObject::Type() } };

	Core::Rtti* Armature::Type() {
		return &ArmatureType;
	}

	Armature::Armature()
	{
    }

    Armature::~Armature()
    {
    }

    void Armature::SetName(const Core::String& value)
    {
        m_name = value;
    }

    const Core::String& Armature::GetName() const
    {
        return m_name;
    }

	const Math::vec3* Armature::GetBoneLocalPosition(std::uint32_t index) {
		return &m_bones.at(index).m_local_position;
	}

	const Math::vec3* Armature::GetBoneGlobalPosition(std::uint32_t index) {
		auto& bone = m_bones.at(index);
		if (bone.m_need_update)
			Update();
		return &bone.m_global_position;
	}

	const Math::quat* Armature::GetBoneLocalRotation(std::uint32_t index) {
		return &m_bones.at(index).m_local_rotation;
	}

	const Math::quat* Armature::GetBoneGlobalRotation(std::uint32_t index) {
		auto& bone = m_bones.at(index);
		if (bone.m_need_update)
			Update();
		return &bone.m_global_rotation;
	}

	void Armature::SetBoneLocalPosition(std::uint32_t index, const Math::vec3& value) {
		m_bones.at(index).m_local_position = value;
		m_bones.at(index).m_need_update = true;
	}

	void Armature::SetBoneGlobalPosition(std::uint32_t index, const Math::vec3& value) {
	}

	void Armature::SetBoneLocalRotation(std::uint32_t index, const Math::quat& value) {
		m_bones.at(index).m_local_rotation = value;
		m_bones.at(index).m_need_update = true;
	}

	void Armature::SetBoneGlobalRotation(std::uint32_t index, const Math::quat& value) {

	}

	const IArmatureSchema* Armature::GetSchema() const {
		return m_schema;
	}

	void Armature::SetSchema(IArmatureSchema* value) {
		m_schema = value;
	}

	void Armature::SetSchemaName(const Core::String& value) {
		m_schema_name = value;
	}

	const Core::String& Armature::GetSchemaName() const {
		return m_schema_name;
	}

	void Armature::Update() {
		std::stack<IBone*> bones;
		for (int i = 0, max_i = m_schema->GetRootBonesCount(); i < max_i; ++i) {
			bones.push(m_schema->GetRootBone(i));			
			while (!bones.empty()) {
				IBone* bone = bones.top();
				bones.pop();

				BoneCache& cache = m_bones.at(bone->GetIndex());
				if (cache.m_need_update) {
					if (bone->HasParent()) {
						const BoneCache& parent_cache = m_bones.at(bone->GetParent());
						cache.m_global_position = parent_cache.m_global_position + parent_cache.m_global_rotation.Rotate(cache.m_local_position);
						cache.m_global_rotation = parent_cache.m_global_rotation * cache.m_local_rotation;
					}
					else {
						cache.m_global_position = cache.m_local_position;
						cache.m_global_rotation = cache.m_local_rotation;
					}
					cache.m_need_update = false;
					for (int i = 0, max_i = bone->GetChildrenCount(); i < max_i; ++i) {
						bones.push(m_schema->GetBone(bone->GetChild(i)));
					}
				}
			}
		}
	}
}
PUNK_ENGINE_END
