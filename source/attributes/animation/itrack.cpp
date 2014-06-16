#include <list>
#include <core/ifactory.h>
#include "itrack.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class TrackImpl : public ITrack {
	public:

		~TrackImpl() {
			while (!m_frames.empty()) {
				m_frames.back()->Release();
				m_frames.pop_back();
			}
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_ITrack });
		}

		std::uint32_t AddRef() {
			return m_ref_count.fetch_add(1);
		}
		std::uint32_t Release() {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		
		std::uint32_t GetDuration() const override {
			return m_last_frame - m_first_frame + 1;
		}

		std::int32_t GetFirstFrame() const  override {
			return m_first_frame;
		}

		std::int32_t GetLastFrame() const override {
			return m_last_frame;
		}

		void SetFirstFrame(std::int32_t value) override {
			m_first_frame = value;
		}

		void SetLastFrame(std::int32_t value) override {
			m_last_frame = value;
		}

		IKeyFrame* GetKeyBefore(std::int32_t frame) {
			if (m_frames.empty())
				return nullptr;
			auto cur = m_frames.begin();
			auto prev = cur;
			while (cur != m_frames.end()) {
				if ((*cur)->GetFrame() > frame)
					return *prev;
				prev = cur;
				++cur;
			}			
			return m_frames.front();
		}

		IKeyFrame* GetKeyAfter(std::int32_t frame) {
			if (m_frames.empty())
				return nullptr;
			auto cur = m_frames.begin();
			auto next = cur;
			while (cur != m_frames.end()) {
				if ((*cur)->GetFrame() > frame)
					return *cur;
				++cur;
			}
			return m_frames.back();
		}

		void AddKeyFrame(IKeyFrame* value) {
			if (m_frames.empty())
				m_frames.push_back(value);
			else {
				auto it = m_frames.begin();
				while (it != m_frames.end()) {
					if ((*it)->GetFrame() > value->GetFrame()) {
						break;
					}
				}
				m_frames.insert(it, value);
			}
		}

		const Core::String& GetName() const {
			return m_name;
		}

		void SetName(const Core::String& value) {
			m_name = value;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count;
		std::int32_t m_first_frame{ 0 };
		std::int32_t m_last_frame{ 0 };
		std::list<IKeyFrame*> m_frames;
		Core::String m_name;
	};

	PUNK_REGISTER_CREATOR(IID_ITrack, (Core::CreateInstance<TrackImpl, ITrack>));
}
PUNK_ENGINE_END
