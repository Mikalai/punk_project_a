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
	struct tagLinear;

	template<typename T, typename Tag> struct InterpolationAspect;
	template<typename T, typename Tag> struct GuidAspect;

	template<> struct GuidAspect < Math::vec3, tagLinear > { static const Core::Guid GetGuid() { return IID_IVec3KeyFrameLinearInterpolator; } };
	template<> struct GuidAspect < Math::vec4, tagLinear > { static const Core::Guid GetGuid() { return IID_IVec4KeyFrameLinearInterpolator; } };
	template<> struct GuidAspect < Math::mat4, tagLinear > { static const Core::Guid GetGuid() { return IID_IMat4KeyFrameLinearInterpolator; } };
	template<> struct GuidAspect < Math::quat, tagLinear > { static const Core::Guid GetGuid() { return IID_IQuatKeyFrameLinearInterpolator; } };
	template<> struct GuidAspect < float, tagLinear > { static const Core::Guid GetGuid() { return IID_IFloatKeyFrameLinearInterpolator; } };

	template<typename T>
	struct InterpolationAspect < T, tagLinear > : public GuidAspect<T, tagLinear> {

		static const T Interpolate(const T& a, const T& b, float t) {
			return Math::linear_interpolation(a, b, t);
		}
	};

	template<>
	struct InterpolationAspect < Math::quat, tagLinear > : public GuidAspect<Math::quat, tagLinear> {

		static const Math::quat Interpolate(const Math::quat& a, const Math::quat& b, float t) {
			return Math::spherical_linear_interpolation(a, b, t);
		}
	};
	
	template<typename T, typename Tag>
	class KeyFrameInterpolatorImpl : public IKeyFrameInterpolator {
	public:

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

		}
		void Interpolate(std::int32_t frame, void* result, std::uint32_t size) {

		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 1 };

	};

	PUNK_REGISTER_CREATOR(IID_IVec3KeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<Math::vec3, tagLinear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(IID_IVec4KeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<Math::vec4, tagLinear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(IID_IMat4KeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<Math::mat4, tagLinear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(IID_IQuatKeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<Math::quat, tagLinear>, IKeyFrameInterpolator>));
	PUNK_REGISTER_CREATOR(IID_IFloatKeyFrameLinearInterpolator, (Core::CreateInstance<KeyFrameInterpolatorImpl<float, tagLinear>, IKeyFrameInterpolator>));
}
PUNK_ENGINE_END
