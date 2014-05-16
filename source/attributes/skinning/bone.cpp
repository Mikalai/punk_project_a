#include <iostream>
#include <algorithm>

#include <system/logger/module.h>
#include <string/module.h>
#include <math/quat.h>
#include <math/mat4.h>
#include <math/vec3.h>
#include <math/helper.h>
#include "bone.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Bone::Bone() {}

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

	void Bone::AddChild(std::uint32_t index) {
		m_children.push_back(index);
	}

	std::uint32_t Bone::GetChildrenCount() const {
		return (std::uint32_t)m_children.size();
	}

	std::uint32_t Bone::GetChild(std::uint32_t index) {
		return m_children.at(index);
	}

	extern PUNK_ENGINE_API IBoneUniquePtr CreateBone() {
		return IBoneUniquePtr{ new Bone, DestroyBone };
	}

	extern PUNK_ENGINE_API void DestroyBone(IBone* value) {
		Bone* bone = dynamic_cast<Bone*>(value);
		delete bone;
	}
}
PUNK_ENGINE_END
