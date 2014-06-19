#include <system/errors/module.h>
#include <core/ifactory.h>
#include "ianimation.h"
#include "ikeyframe.h"
#include "ikeyframe_interpolator.h"
#include "itrack.h"
#include "ianimation_player.h"
#include "ianimated.h"

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
		void OnAnimationStarted(Core::ActionBase<void>* action) override;
		void OnAnimationEnded(Core::ActionBase<void>* action) override;
		void OnFrame(AnimationAdvanced* action) override;
		void OnFrame(std::int32_t track_index, TrackAdvanced* action) override;
		/*void Attach(IAnimated* value) override;
		void Detach(IAnimated* value) override;*/

	private:
		void AdvanceTime(AnimationSeekDirection dir, float dt);
		std::int32_t GetCurrentFrame();
		void SetupInterpolators();

	private:
		AnimationPlaybackType m_playback_type{ AnimationPlaybackType::Loop };
		bool m_active{ false };
		std::int32_t m_prev_frame{ 0 };
		float m_duration{ 1 };
		float m_current_time{ 0 };
		float m_dir_factor{ 1 };	//	can be -1 or 1
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		InterpolatorType m_interpolator_type{ InterpolatorType::Linear };
		IAnimation* m_animation{ nullptr };
		Core::ActionSlot<void> m_on_started;
		Core::ActionSlot<void> m_on_ended;
		Core::ActionSlot<std::int32_t> m_on_frame;

		struct TrackCache {
			Core::ActionSlot<std::int32_t, void*, std::uint32_t> m_on_frame;
			std::vector<std::uint8_t> m_current_value;
			IKeyFrameInterpolator* m_interpolator{ nullptr };

			~TrackCache() {
				if (m_interpolator) {
					m_interpolator->Release();
					m_interpolator = nullptr;
				}
			}
		};
		std::vector<TrackCache> m_track_cache;
		//std::vector<Core::UniquePtr<IAnimated>> m_animated;
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
		if (frame != m_prev_frame) {
			m_prev_frame = frame;
			m_on_frame(frame);
			for (std::uint32_t i = 0, max_i = m_animation->GetTracksCount(); i < max_i; ++i) {
				m_track_cache[i].m_interpolator->Interpolate(frame, m_track_cache.at(i).m_current_value.data(), m_track_cache.at(i).m_current_value.size());
				m_track_cache[i].m_on_frame(frame, m_track_cache.at(i).m_current_value.data(), m_track_cache.at(i).m_current_value.size());
				/*for (auto& animated : m_animated) {
					animated->Advance(i, frame, m_track_cache.at(i).m_current_value.data(), m_track_cache.at(i).m_current_value.size());
				}*/
			}
		}
	}

	//void AnimationPlayerImpl::Attach(IAnimated* value) {
	//	value->AddRef();
	//	m_animated.push_back(Core::UniquePtr < IAnimated > {value, Core::DestroyObject});
	//}

	//void AnimationPlayerImpl::Detach(IAnimated* value) {
	//	auto it = std::find_if(m_animated.begin(), m_animated.end(), [&value](Core::UniquePtr<IAnimated>& anim) -> bool {
	//		return anim.get() == value;
	//	});
	//	if (it != m_animated.end()) {
	//		(*it)->Release();
	//		m_animated.erase(it);
	//	}
	//}

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
			m_track_cache.resize(m_animation->GetTracksCount());
			for (std::int32_t i = 0, max_i = m_animation->GetTracksCount(); i < max_i; ++i) {
				auto track = m_animation->GetTrack(i);
				m_track_cache.at(i).m_current_value.resize(track->GetKeySize());
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
		auto& value = m_track_cache.at(track_index).m_current_value;
		if (value.size() != size)
			throw System::Error::SystemException("Size mismatch");
		memcpy(buffer, value.data(), size);
	}

	void AnimationPlayerImpl::SetupInterpolators() {

		//	if no animation no interpolators can be created
		if (!m_animation)
			return;

		for (std::uint32_t i = 0, max_i = m_animation->GetTracksCount(); i < max_i; ++i) {
			auto track = m_animation->GetTrack(i);
			{
				Core::UniquePtr<Track<float>> float_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IFloatTrack, (void**)&float_track);
				if (float_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IFloatKeyFrameLinearInterpolator, (void**)&m_track_cache.at(i).m_interpolator);
			}
			{
				Core::UniquePtr<Track<Math::vec3>> vec3_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IVec3Track, (void**)&vec3_track);
				if (vec3_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IVec3KeyFrameLinearInterpolator, (void**)&m_track_cache.at(i).m_interpolator);
			}
			{
				Core::UniquePtr<Track<Math::vec4>> vec4_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IVec4Track, (void**)&vec4_track);
				if (vec4_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IVec4KeyFrameLinearInterpolator, (void**)&m_track_cache.at(i).m_interpolator);
			}
			{
				Core::UniquePtr<Track<Math::mat4>> mat4_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IMat4Track, (void**)&mat4_track);
				if (mat4_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IMat4KeyFrameLinearInterpolator, (void**)&m_track_cache.at(i).m_interpolator);
			}
			{
				Core::UniquePtr<Track<Math::quat>> quat_track{ nullptr, Core::DestroyObject };
				track->QueryInterface(IID_IQuatTrack, (void**)&quat_track);
				if (quat_track && m_interpolator_type == InterpolatorType::Linear)
					Core::GetFactory()->CreateInstance(IID_IQuatKeyFrameLinearInterpolator, (void**)&m_track_cache.at(i).m_interpolator);
			}
			m_track_cache.at(i).m_interpolator->SetTrack(track);
		}
	}

	std::int32_t AnimationPlayerImpl::GetCurrentFrame() {
		auto frames = m_animation->GetDuration();
		std::int32_t frame = m_animation->GetFirstFrame() + std::int32_t((float)frames / m_duration * m_current_time);
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

	void AnimationPlayerImpl::OnAnimationStarted(Core::ActionBase<void>* action) {
		m_on_started.Add(action);
	}

	void AnimationPlayerImpl::OnAnimationEnded(Core::ActionBase<void>* action) {
		m_on_ended.Add(action);
	}
	void AnimationPlayerImpl::OnFrame(AnimationAdvanced* action) {
		m_on_frame.Add(action);
	}

	void AnimationPlayerImpl::OnFrame(std::int32_t track_index, TrackAdvanced* action) {
		if (!m_animation)
			return;
		m_track_cache.at(track_index).m_on_frame.Add(action);
	}

	PUNK_REGISTER_CREATOR(IID_IAnimationPlayer, (Core::CreateInstance<AnimationPlayerImpl, IAnimationPlayer>));

}
PUNK_ENGINE_END
