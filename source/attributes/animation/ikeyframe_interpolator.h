#ifndef _H_PUNK_VIRTUAL_OBJECT_ANIMATION
#define _H_PUNK_VIRTUAL_OBJECT_ANIMATION

#include <core/iobject.h>
#include "ikeyframe.h"
#include "itrack.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	DECLARE_PUNK_GUID(IID_IKeyFrameInterpolator, "DD4F6B2A-304D-444C-9699-849DDE9A95C1");
	DECLARE_PUNK_GUID(IID_IKeyFrameLinearInterpolator, "E64F443F-A5BA-4E58-9ED1-EB819E53CC7B");
	DECLARE_PUNK_GUID(IID_IVec3KeyFrameLinearInterpolator, "987196BC-1D7D-4F2F-90BB-75CE6C5DBF26");
	DECLARE_PUNK_GUID(IID_IVec4KeyFrameLinearInterpolator, "1A7F76D9-A19A-4675-9ECD-1AAF7F92F052");
	DECLARE_PUNK_GUID(IID_IMat4KeyFrameLinearInterpolator, "C0F2C6D3-B030-4FCD-9D40-B31E9E9B9242");
	DECLARE_PUNK_GUID(IID_IQuatKeyFrameLinearInterpolator, "9B29CF1A-3709-4AE0-A2B2-E3CB531E17D5");
	DECLARE_PUNK_GUID(IID_IFloatKeyFrameLinearInterpolator, "48B3B926-FB9C-4D09-9AEE-99369F53AD4D");

	enum class InterpolatorType : std::uint32_t {
		Linear
	};

    class IKeyFrameInterpolator : public Core::IObject
	{
	public:
		virtual InterpolatorType GetType() = 0;
		virtual void SetTrack(ITrack* track) = 0;
		virtual void Interpolate(std::int32_t frame, void* result, std::uint32_t size) = 0;
	};

	template<typename T>
	class KeyFrameInterpolator : public IKeyFrameInterpolator {
	public:
		const T Interpolate(std::int32_t frame) {
			T result;
			Interpolate(frame, &result, sizeof(result));
			return result;
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_VIRTUAL_OBJECT_ANIMATION
