#include <memory.h>
#include <system/errors/module.h>
#include <system/factory/module.h>
#include <math/interpolation.h>
#include <math/forward.h>
#include <math/matrix.h>
#include "ikeyframe_interpolator.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	template<typename T, InterpolatorType Tag> struct InterpolationAspect;
	template<typename T, InterpolatorType Tag> struct InterpolatorGuidAspect;

	template<> struct InterpolatorGuidAspect < Math::vec3, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return CLSID_Vec3KeyFrameLinearInterpolator; } };
	template<> struct InterpolatorGuidAspect < Math::vec4, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return CLSID_Vec4KeyFrameLinearInterpolator; } };
	template<> struct InterpolatorGuidAspect < Math::mat4, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return CLSID_Mat4KeyFrameLinearInterpolator; } };
	template<> struct InterpolatorGuidAspect < Math::quat, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return CLSID_QuatKeyFrameLinearInterpolator; } };
	template<> struct InterpolatorGuidAspect < float, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return CLSID_FloatKeyFrameLinearInterpolator; } };

	template<typename T>
	struct InterpolationAspect < T, InterpolatorType::Linear> : public InterpolatorGuidAspect<T, InterpolatorType::Linear>{

		static const T Interpolate(const T& a, const T& b, float t) {
			return Math::linear_interpolation(a, b, t);
		}

		static const InterpolatorType Type() {
			return InterpolatorType::Linear;
		}
	};

	template<>
	struct InterpolationAspect < Math::quat, InterpolatorType::Linear > : public InterpolatorGuidAspect<Math::quat, InterpolatorType::Linear>{

		static const Math::quat Interpolate(const Math::quat& a, const Math::quat& b, float t) {
			return Math::spherical_linear_interpolation(a, b, t);
		}

		static const InterpolatorType Type() {
			return InterpolatorType::Linear;
		}
	};
	
	template<typename T, InterpolatorType Tag>
	class KeyFrameInterpolatorImpl : public IKeyFrameInterpolator {
	public:

        KeyFrameInterpolatorImpl()
            : m_ref_count{ 0 }
        {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IKeyFrameInterpolator, InterpolationAspect<T, Tag>::GetGuid() });
		}
		
		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		//	IKeyFrameInterpolator
		void SetTrack(Core::Pointer<ITrack> track, float duration) override {			
			m_track = track;			
			m_duration = duration;
		}

		std::int32_t GetCurrentFrame(float current_time) {
			LOG_FUNCTION_SCOPE();
			auto frames = m_track->GetDuration();
			std::int32_t frame = m_track->GetFirstFrame() + std::int32_t((float)frames / m_duration * current_time);
			return frame;
		}

		void Interpolate(float time, void* result, std::uint32_t size) {
			if (!m_track)
				throw System::Error::SystemException("Track not set");
			
			auto frame = GetCurrentFrame(time);

			KeyFrame<T>* before = m_track->KeyBefore(frame);
			KeyFrame<T>* after = m_track->KeyAfter(frame);
			float before_time = m_duration / (float)m_track->GetDuration() * (before->GetFrame() - m_track->GetFirstFrame());
			float after_time = m_duration / (float)m_track->GetDuration() * (after->GetFrame() - m_track->GetFirstFrame());
			T value;
			if (before != after) {
				float t = (time - before_time) / (after_time - before_time);
				value = InterpolationAspect<T, Tag>::Interpolate(before->Key(), after->Key(), t);				
			}
			else {
				value = before->Key();
			}
			memcpy(result, &value, size);
		}

		InterpolatorType GetType() override {
			return Tag;
		}

		void SetDuration(float duration) override {
			m_duration = duration;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::Pointer<Track<T>> m_track{ nullptr, Core::DestroyObject };
		float m_duration{ 1 };
	};

	PUNK_REGISTER_CREATOR(CLSID_Vec3KeyFrameLinearInterpolator, (System::CreateInstance<KeyFrameInterpolatorImpl<Math::vec3, InterpolatorType::Linear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(CLSID_Vec4KeyFrameLinearInterpolator, (System::CreateInstance<KeyFrameInterpolatorImpl<Math::vec4, InterpolatorType::Linear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(CLSID_Mat4KeyFrameLinearInterpolator, (System::CreateInstance<KeyFrameInterpolatorImpl<Math::mat4, InterpolatorType::Linear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(CLSID_QuatKeyFrameLinearInterpolator, (System::CreateInstance<KeyFrameInterpolatorImpl<Math::quat, InterpolatorType::Linear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(CLSID_FloatKeyFrameLinearInterpolator, (System::CreateInstance<KeyFrameInterpolatorImpl<float, InterpolatorType::Linear>, IKeyFrameInterpolator>));
}
PUNK_ENGINE_END
