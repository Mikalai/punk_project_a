#include <core/ifactory.h>
#include <attributes/animation/module.h>
#include <system/logger/module.h>
#include <math/matrix_helper.h>
#include "transform.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{	
	Transform::Transform(const Math::mat4& m)
	{
		m_transform = m;
	}

    Transform::Transform()
    {}

	Transform::~Transform()
    {
	}

	void Transform::SetAnimationData(IAnimation* value) {
		if (value == m_animation_data.get())
			return;

		value->AddRef();
		m_animation_data.reset(value);

		m_position_track_index = -1;
		m_scale_track_index = -1;
		m_rotation_track_index = -1;
		for (std::uint32_t i = 0, max_i = m_animation_data->GetTracksCount(); i < max_i; ++i) {
			auto track = m_animation_data->GetTrack(i);
			if (track->GetName() == L"Position") {
				m_position_track_index = i;
			}
			else if (track->GetName() == L"Rotation") {
				m_rotation_track_index = i;
			}
			else if (track->GetName() == L"Scale") {
				m_scale_track_index = i;
			}
		}
	}

	IAnimation* Transform::GetAnimationData() {
		return m_animation_data.get();
	}

	void Transform::AddAnimation(const Core::String& name) {
		m_supported_animations.push_back(name);
	}

	std::uint32_t Transform::GetAnimationsCount() const {
		return (std::uint32_t)m_supported_animations.size();
	}
	
	const Core::String& Transform::GetAnimation(std::uint32_t index) const {
		return m_supported_animations.at(index);
	}

	void Transform::Advance(std::int32_t track_index, std::int32_t frame, void* data, std::int32_t value) {
		if (track_index == m_position_track_index) {
			Math::vec3* value = (Math::vec3*)data;
			m_position = *value;
			m_need_update = true;
		}
		else if (track_index == m_rotation_track_index) {
			Math::quat* value = (Math::quat*)data;
			m_rotation = *value;
			m_need_update = true;
		}
		else if (track_index == m_scale_track_index) {
			Math::vec3* value = (Math::vec3*)data;
			m_scale = *value;
			m_need_update = true;
		}
	}

	void Transform::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

		if (type == Core::IID_IObject) {
			*object = (Core::IObject*)(ITransform*)this;
			AddRef();
		}
		else if (type == IID_ITransform) {
			*object = (void*)(ITransform*)this;
			AddRef();
		}
		else if (type == IID_IAnimated) {
			*object = (void*)(IAnimated*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	std::uint32_t Transform::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Transform::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

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

	PUNK_REGISTER_CREATOR(IID_ITransform, (Core::CreateInstance<Transform, ITransform>));
}
PUNK_ENGINE_END
