#include <list>
#include <core/ifactory.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include <math/quat.h>
#include "itrack.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	template<class T>
	class TrackImpl : public Track<T> {
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
			value->AddRef();
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

		std::uint32_t GetKeySize() const override {
			return sizeof(T);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count;
		std::int32_t m_first_frame{ 0 };
		std::int32_t m_last_frame{ 0 };
		std::list<IKeyFrame*> m_frames;
		Core::String m_name;
	};

	PUNK_REGISTER_CREATOR(IID_IFloatTrack, (Core::CreateInstance<TrackImpl<float>, ITrack>));
	PUNK_REGISTER_CREATOR(IID_IVec3Track, (Core::CreateInstance<TrackImpl<Math::vec3>, ITrack>));
	PUNK_REGISTER_CREATOR(IID_IVec4Track, (Core::CreateInstance<TrackImpl<Math::vec4>, ITrack>));
	PUNK_REGISTER_CREATOR(IID_IQuatTrack, (Core::CreateInstance<TrackImpl<Math::quat>, ITrack>));
	PUNK_REGISTER_CREATOR(IID_IMat4Track, (Core::CreateInstance<TrackImpl<Math::mat4>, ITrack>));
}
PUNK_ENGINE_END
