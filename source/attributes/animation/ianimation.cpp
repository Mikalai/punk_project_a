#include <system/factory/module.h>
#include <system/logger/module.h>
#include "ianimation.h"

PUNK_ENGINE_BEGIN
namespace Attributes {


	class Animation : public IAnimation {
	public:
        Animation();
        virtual ~Animation();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IAnimation
		std::uint32_t GetDuration() const override;
		std::int32_t GetFirstFrame() const override;
		std::int32_t GetLastFrame() const override;
		void AddTrack(ITrack* value) override;
		std::uint32_t GetTracksCount() const override;
		const ITrack* GetTrack(std::uint32_t index) const override;
		ITrack* GetTrack(std::uint32_t index) override;
		void SetName(const Core::String& value) override;
		const Core::String& GetName() const override;
		std::uint32_t GetTrackIndex(const Core::String& name) override;
	private:
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		std::vector<ITrack*> m_tracks;
		Core::String m_name;
	};

    Animation::Animation()
        : m_ref_count{1}
    {
        LOG_FUNCTION_SCOPE
    }

	Animation::~Animation() {        
        LOG_FUNCTION_SCOPE
		while (!m_tracks.empty()) {
			m_tracks.back()->Release();
			m_tracks.pop_back();
		}
	}

	//	IObject
	void Animation::QueryInterface(const Core::Guid& type, void** object) {
        LOG_FUNCTION_SCOPE
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IAnimation });
	}

	std::uint32_t Animation::AddRef() {
        LOG_FUNCTION_SCOPE
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Animation::Release() {
        LOG_FUNCTION_SCOPE
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

	//	IAnimation
	std::uint32_t Animation::GetDuration() const {        
		return GetLastFrame() - GetFirstFrame() + 1;
	}

	std::int32_t Animation::GetFirstFrame() const {
		if (m_tracks.empty())
			return 0;

		std::int32_t frame = m_tracks.front()->GetFirstFrame();
		for (auto track : m_tracks) {
			if (frame > track->GetFirstFrame())
				frame = track->GetFirstFrame();
		}
		return frame;
	}

	std::int32_t Animation::GetLastFrame() const {
		if (m_tracks.empty())
			return 0;

		std::int32_t frame = m_tracks.front()->GetLastFrame();
		for (auto track : m_tracks) {
			if (frame < track->GetLastFrame())
				frame = track->GetLastFrame();
		}
		return frame;
	}

	void Animation::AddTrack(ITrack* value) {
		value->AddRef();
		m_tracks.push_back(value);
	}

	std::uint32_t Animation::GetTracksCount() const {
		return (std::uint32_t)m_tracks.size();
	}

	const ITrack* Animation::GetTrack(std::uint32_t index) const {
		return m_tracks.at(index);
	}

	ITrack* Animation::GetTrack(std::uint32_t index) {
		return m_tracks.at(index);
	}

	void Animation::SetName(const Core::String& value) {
		m_name = value;
	}

	const Core::String& Animation::GetName() const {
		return m_name;
	}

	std::uint32_t Animation::GetTrackIndex(const Core::String& name) {
		for (std::uint32_t i = 0, max_i = GetTracksCount(); i < max_i; ++i) {
			auto track = GetTrack(i);
			if (track->GetName() == name)
				return i;
		}
		return (std::uint32_t)(-1);
	}

    PUNK_REGISTER_CREATOR(IID_IAnimation, (System::CreateInstance<Animation, IAnimation>));
	
}
PUNK_ENGINE_END
