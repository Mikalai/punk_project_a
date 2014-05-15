#include <system/logger/module.h>
#include <math/matrix_helper.h>
#include "transform.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti TransformType{ "Attributes.Transform", typeid(Transform).hash_code(), { Core::IObject::Type() } };

	Core::Rtti* Transform::Type() {
		return &TransformType;
	}

	Transform::Transform(const Math::mat4& m)
	{
		m_transform = m;
	}

    Transform::Transform()
    {}

	Transform::~Transform()
    {}

	void Transform::SetMatrix(const Math::mat4& value) {
		m_transform = value;
		Math::Decompose(m_transform, m_position, m_rotation, m_scale);
		m_need_update = false;
	}

	const Math::mat4& Transform::GetMatrix() const {
		if (m_need_update) {
			m_transform = Math::CreatePositionRotationScaleMatrix(m_position, m_rotation, m_scale);
			m_need_update = false;
		}
		return m_transform;
	}
	
	Math::mat4& Transform::GetMatrix() {
		return const_cast<Math::mat4&>(static_cast<const Transform&>(*this).GetMatrix());
	}

	void Transform::SetPosition(const Math::vec3& value) {
		m_position = value;
		m_need_update = true;
	}
	
	const Math::vec3& Transform::GetPosition() const {
		return m_position;
	}

	void Transform::SetRotation(const Math::quat& value) {
		m_rotation = value;
		m_need_update = true;
	}

	const Math::quat& Transform::GetRotation() const {
		return m_rotation;
	}

	void Transform::SetScale(const Math::vec3& value) {
		m_scale = value;
		m_need_update = true;
	}

	const Math::vec3& Transform::GetScale() const {
		return m_scale;
	}
}
PUNK_ENGINE_END
