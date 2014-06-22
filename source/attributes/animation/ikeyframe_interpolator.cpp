#include <memory.h>
#include <system/errors/module.h>
#include <core/ifactory.h>
#include <math/interpolation.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include <math/quat.h>
#include "ikeyframe_interpolator.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	template<typename T, InterpolatorType Tag> struct InterpolationAspect;
	template<typename T, InterpolatorType Tag> struct InterpolatorGuidAspect;

	template<> struct InterpolatorGuidAspect < Math::vec3, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return IID_IVec3KeyFrameLinearInterpolator; } };
	template<> struct InterpolatorGuidAspect < Math::vec4, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return IID_IVec4KeyFrameLinearInterpolator; } };
	template<> struct InterpolatorGuidAspect < Math::mat4, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return IID_IMat4KeyFrameLinearInterpolator; } };
	template<> struct InterpolatorGuidAspect < Math::quat, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return IID_IQuatKeyFrameLinearInterpolator; } };
	template<> struct InterpolatorGuidAspect < float, InterpolatorType::Linear > { static const Core::Guid GetGuid() { return IID_IFloatKeyFrameLinearInterpolator; } };

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
            : m_ref_count{1}
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
		void SetTrack(ITrack* track) override {			
			m_track = dynamic_cast<Track<T>*>(track);			
			m_track->AddRef();
		}

		void Interpolate(std::int32_t frame, void* result, std::uint32_t size) {
			if (!m_track)
				throw System::Error::SystemException("Track not set");

			KeyFrame<T>* before = m_track->KeyBefore(frame);
			KeyFrame<T>* after = m_track->KeyAfter(frame);
			T value;
			if (before != after) {
				float t = (frame - before->GetFrame()) / (float)(after->GetFrame() - before->GetFrame());
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

	private:
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		Track<T>* m_track{ nullptr };

	};

	PUNK_REGISTER_CREATOR(IID_IVec3KeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<Math::vec3, InterpolatorType::Linear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(IID_IVec4KeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<Math::vec4, InterpolatorType::Linear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(IID_IMat4KeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<Math::mat4, InterpolatorType::Linear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(IID_IQuatKeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<Math::quat, InterpolatorType::Linear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(IID_IFloatKeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<float, InterpolatorType::Linear>, IKeyFrameInterpolator>));
}
PUNK_ENGINE_END
