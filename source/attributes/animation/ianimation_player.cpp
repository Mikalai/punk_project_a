#include <system/errors/module.h>
#include <core/ifactory.h>
#include "ianimation.h"
#include "ikeyframe.h"
#include "ikeyframe_interpolator.h"
#include "itrack.h"
#include "ianimation_player.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class AnimationPlayerImpl : public IAnimationPlayer {
	public:

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object);
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IAnimationPlayer
		void Start() override;
		void Stop() override;
		bool IsPlaying() const override;
		void SetPlaybackType(AnimationPlaybackType value) override;
		AnimationPlaybackType GetPlaybackType() const override;
		void SetDuration(float time_s) override;
		float GetDuration() const override;
		void Seek(AnimationSeekDirection direction, float dt) override;
		void SetAnimation(IAnimation* value) override;
		const IAnimation* GetAnimation() const override;
		IAnimation* GetAnimation() override;
		void SetKeyFrameInterpolator(InterpolatorType value) override;
		InterpolatorType GetKeyFrameInterpolator() override;
		void GetCurrentValue(std::uint32_t track_index, void* buffer, std::uint32_t size) override;

	private:
		void AdvanceTime(AnimationSeekDirection dir, float dt);
		std::int32_t GetCurrentFrame();
		void SetupInterpolators();

	private:
		AnimationPlaybackType m_playback_type{ AnimationPlaybackType::Loop };
		bool m_active{ false };
		float m_duration{ 1 };
		float m_current_time{ 0 };
		float m_dir_factor{ 1 };	//	can be -1 or 1
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		InterpolatorType m_interpolator_type{ InterpolatorType::Linear };
		IAnimation* m_animation{ nullptr };
		std::vector<std::vector<std::uint8_t>> m_current_value;
		std::vector<IKeyFrameInterpolator*> m_interpolators;
	};

	//	IObject
	void AnimationPlayerImpl::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IAnimationPlayer });
	}

	std::uint32_t AnimationPlayerImpl::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t AnimationPlayerImpl::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

	//	IAnimationPlayer
	void AnimationPlayerImpl::Start() {
		m_active = true;
	}

	void AnimationPlayerImpl::Stop() {
		m_active = false;
	}

	bool AnimationPlayerImpl::IsPlaying() const {
		return m_active;
	}

	void AnimationPlayerImpl::SetPlaybackType(AnimationPlaybackType value) {
		m_playback_type = value;
	}
	AnimationPlaybackType AnimationPlayerImpl::GetPlaybackType() const {
		return m_playback_type;
	}

	void AnimationPlayerImpl::SetDuration(float time_s) {
		m_duration = time_s;
	}

	float AnimationPlayerImpl::GetDuration() const {
		return m_duration;
	}

	void AnimationPlayerImpl::Seek(AnimationSeekDirection direction, float dt) {
		AdvanceTime(direction, dt);
		auto frame = GetCurrentFrame();		
		for (std::uint32_t i = 0, max_i = m_animation->GetTracksCount(); i < max_i; ++i) {
			m_interpolators[i]->Interpolate(frame, m_current_value.at(i).data(), m_current_value.at(i).size());
		}
	}

	void AnimationPlayerImpl::SetAnimation(IAnimation* value) {
		if (value == m_animation)
			return;

		if (m_animation) {
			m_animation->Release();
		}
		
		if (value) {
			value->AddRef();
			m_animation = value;
			//	allocate memory for interpolated data
			m_current_value.resize(m_animation->GetTracksCount());			
			for (std::int32_t i = 0, max_i = m_animation->GetTracksCount(); i < max_i; ++i) {
				auto track = m_animation->GetTrack(i);
				m_current_value.at(i).resize(track->GetKeySize());
			}
		}

		//	setup interpolator for each track of the new animation
		SetupInterpolators();
	}

	const IAnimation* AnimationPlayerImpl::GetAnimation() const {
		return m_animation;
	}

	IAnimation* AnimationPlayerImpl::GetAnimation() {
		return m_animation;
	}

	void AnimationPlayerImpl::SetKeyFrameInterpolator(InterpolatorType value) {	
		m_interpolator_type = value;
	}

	InterpolatorType AnimationPlayerImpl::GetKeyFrameInterpolator() {
		return m_interpolator_type;
	}
	
	void AnimationPlayerImpl::GetCurrentValue(std::uint32_t track_index, void* buffer, std::uint32_t size) {
		auto& value = m_current_value.at(track_index);
		if (value.size() != size)
			throw System::Error::SystemException("Size mismatch");
		memcpy(buffer, value.data(), size);
	}

	void AnimationPlayerImpl::SetupInterpolators() {
		//	clear old interpolators
		while (!m_interpolators.empty()) {
			m_interpolators.back()->Release();
			m_interpolators.pop_back();
		}

		//	if no animation no interpolators can be created
		if (!m_animation)
			return;

		m_interpolators.resize(m_animation->GetTracksCount());
		for (std::uint32_t i = 0, max_i = m_animation->GetTracksCount(); i < max_i; ++i) {
			auto track = m_animation->GetTrack(i);
			{
				Core::UniquePtr<Track<float>> float_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IFloatTrack, (void**)&float_track);
				if (float_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IFloatKeyFrameLinearInterpolator, (void**)&m_interpolators.at(i));
			}			
			{
				Core::UniquePtr<Track<Math::vec3>> vec3_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IVec3Track, (void**)&vec3_track);
				if (vec3_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IVec3KeyFrameLinearInterpolator, (void**)&m_interpolators.at(i));
			}
			{
				Core::UniquePtr<Track<Math::vec4>> vec4_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IVec4Track, (void**)&vec4_track);
				if (vec4_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IVec4KeyFrameLinearInterpolator, (void**)&m_interpolators.at(i));
			}
			{
				Core::UniquePtr<Track<Math::mat4>> mat4_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IMat4Track, (void**)&mat4_track);
				if (mat4_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IMat4KeyFrameLinearInterpolator, (void**)&m_interpolators.at(i));
			}
			{
				Core::UniquePtr<Track<Math::quat>> quat_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IQuatTrack, (void**)&quat_track);
				if (quat_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IQuatTrack, (void**)&m_interpolators.at(i));
			}
			m_interpolators.at(i)->SetTrack(track);
		}
	}

	std::int32_t AnimationPlayerImpl::GetCurrentFrame() {		
		auto frames = m_animation->GetDuration();
		std::int32_t frame = std::int32_t((float)frames / m_duration * m_current_time);
		return frame;
	}

	void AnimationPlayerImpl::AdvanceTime(AnimationSeekDirection dir, float dt) {
		if (dir == AnimationSeekDirection::Begin) {
			m_current_time = dt;
			m_dir_factor = 1;
		}
		else if (dir == AnimationSeekDirection::End) {
			m_current_time = m_duration - dt;
			m_dir_factor = 1;
		}
		else if (dir == AnimationSeekDirection::Current) {
			m_current_time += dt * m_dir_factor;
			if (m_current_time < 0) {
				if (m_playback_type == AnimationPlaybackType::Once)
					m_current_time = 0;
				if (m_playback_type == AnimationPlaybackType::Loop)
					m_current_time = m_duration;
				if (m_playback_type == AnimationPlaybackType::PingPong) {
					m_dir_factor = -m_dir_factor;
					m_current_time = 0;
				}
			}
			else if (m_current_time >= m_duration) {
				if (m_playback_type == AnimationPlaybackType::Once)
					m_current_time = m_duration;
				if (m_playback_type == AnimationPlaybackType::Loop)
					m_current_time = 0;
				if (m_playback_type == AnimationPlaybackType::PingPong) {
					m_dir_factor = -m_dir_factor;
					m_current_time = m_duration;
				}
			}
		}
	}

	PUNK_REGISTER_CREATOR(IID_IAnimationPlayer, (Core::CreateInstance<AnimationPlayerImpl, IAnimationPlayer>));

}
PUNK_ENGINE_END
