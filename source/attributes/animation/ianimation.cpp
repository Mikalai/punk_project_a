#include "ianimation.h"

PUNK_ENGINE_BEGIN
namespace Attributes {


	class Animation : public IAnimation {
	public:
		~Animation();

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

	private:
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		std::vector<ITrack*> m_tracks;
		Core::String m_name;
	};

	Animation::~Animation() {
		while (!m_tracks.empty()) {
			m_tracks.back()->Release();
			m_tracks.pop_back();
		}
	}

	//	IObject
	void Animation::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IAnimation });
	}

	std::uint32_t Animation::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Animation::Release() {
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

		std::int32_t frame = m_tracks.front()->GetFirstFrame();
		for (auto track : m_tracks) {
			if (frame < track->GetFirstFrame())
				frame = track->GetFirstFrame();
		}
		return frame;
	}

	void Animation::AddTrack(ITrack* value) {
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

}
PUNK_ENGINE_END
