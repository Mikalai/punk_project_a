#include <math/mat4.h>
#include <math/vec3.h>
#include <math/quat.h>
#include <attributes/animation/module.h>
#include "itransform.h"
#include <system/factory/module.h>
#include <attributes/animation/module.h>
#include <system/logger/module.h>
#include <math/matrix_helper.h>
#include "transform.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{	
	class PUNK_ENGINE_LOCAL Transform : public ITransform, public IAnimated
	{
	public:

		Transform();
		Transform(const Transform&) = delete;
		Transform& operator = (const Transform&) = delete;
		Transform(const Math::mat4& m);
		virtual ~Transform();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	ITransform
		void SetMatrix(const Math::mat4& value) override;
		const Math::mat4& GetMatrix() const override;
		Math::mat4& GetMatrix() override;
		void SetPosition(const Math::vec3& value) override;
		const Math::vec3& GetPosition() const override;
		void SetRotation(const Math::quat& value) override;
		const Math::quat& GetRotation() const override;
		void SetScale(const Math::vec3& value) override;
		const Math::vec3& GetScale() const override;

		//	IAnimated
		void SetAnimationPlayer(IAnimationPlayer* value) override {
			if (value == m_animation_player.get())
				return;

			value->AddRef();
			m_animation_player.reset(value);

			m_position_track_index = -1;
			m_scale_track_index = -1;
			m_rotation_track_index = -1;
			for (std::uint32_t i = 0, max_i = m_animation_player->GetAnimation()->GetTracksCount(); i < max_i; ++i) {
				auto track = m_animation_player->GetAnimation()->GetTrack(i);
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

		IAnimationPlayer* GetAnimationPlayer() override {
			return m_animation_player.get();
		}

		void Update() override {		
			if (m_animation_player.get() && m_animation_player->GetAnimation()) {
				for (std::uint32_t track_index = 0, max_i = m_animation_player->GetAnimation()->GetTracksCount(); track_index < max_i; ++track_index) {
					auto track = m_animation_player->GetAnimation()->GetTrack(track_index);
					if (track_index == m_position_track_index) {
						m_animation_player->GetCurrentValue(track_index, (void*)&m_position, sizeof(m_position));
						m_need_update = true;
					}
					else if (track_index == m_rotation_track_index) {
						m_animation_player->GetCurrentValue(track_index, (void*)&m_rotation, sizeof(m_rotation));
						m_need_update = true;
					}
					else if (track_index == m_scale_track_index) {
						m_animation_player->GetCurrentValue(track_index, (void*)&m_scale, sizeof(m_scale));
						m_need_update = true;
					}
				}
			}
		}

		void AddAnimation(const Core::String& name) override;
		std::uint32_t GetAnimationsCount() const override;
		const Core::String& GetAnimation(std::uint32_t index) const override;

	private:
		//	IObject
		std::atomic<std::uint32_t> m_ref_count{ 0 };

		//	IAnimated
		Core::Pointer<IAnimationPlayer> m_animation_player{ nullptr, Core::DestroyObject };
		std::int32_t m_position_track_index{ -1 };
		std::int32_t m_rotation_track_index{ -1 };
		std::int32_t m_scale_track_index{ -1 };
		std::vector<Core::String> m_supported_animations;

		//	ITransform
		mutable Math::mat4 m_transform;
		Math::quat m_rotation;
		Math::vec3 m_position;
		Math::vec3 m_scale;
		mutable bool m_need_update{ true };
	};

	Transform::Transform(const Math::mat4& m)
	{
		m_transform = m;
	}

    Transform::Transform()
    {}

	Transform::~Transform()
    {
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

	PUNK_REGISTER_CREATOR(IID_ITransform, (System::CreateInstance<Transform, ITransform>));
}
PUNK_ENGINE_END
