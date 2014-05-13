#include <iostream>
#include <algorithm>

#include <system/logger/module.h>
#include <string/module.h>
#include <math/quat.h>
#include <math/mat4.h>
#include <math/vec3.h>
#include <math/helper.h>
#include <attributes/animation/armature_animation_mixer.h>

#include "bone.h"
#include "armature.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Bone::~Bone()
	{}

	void Bone::SetIndex(std::uint32_t value) {
		m_index = value;
	}

	std::uint32_t Bone::GetIndex() const {
		return m_index;
	}

	void Bone::SetName(const Core::String& value) {
		m_name = value;
	}

	const Core::String& Bone::GetName() const {
		return m_name;
	}

	void Bone::SetLength(float value) {
		m_length = value;
	}

	float Bone::GetLength() const {
		return m_length;
	}

	void Bone::SetRestMatrix(const Math::mat4& value) {
		m_rest_matrix = value;
	}

	const Math::mat4& Bone::GetRestMatrix() const {
		return m_rest_matrix;
	}

	void Bone::SetParent(std::uint32_t value) {
		m_parent = value;
	}

	std::uint32_t Bone::GetParent() const {
		return m_parent;
	}

	bool Bone::HasParent() const {
		return m_parent != std::numeric_limits<std::uint32_t>::infinity();
	}
}
PUNK_ENGINE_END
