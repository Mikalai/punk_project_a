#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include <string/module.h>
#include "armature.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti ArmatureType{ L"Attributes.Armature", typeid(Armature).hash_code(), { Core::Object::Type() } };

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
}
PUNK_ENGINE_END
