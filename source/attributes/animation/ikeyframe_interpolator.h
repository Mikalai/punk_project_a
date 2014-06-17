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
	DECLARE_PUNK_GUID(IID_IVec3KeyFrameLinearInterpolator, "EA009DC0-B8F6-468C-9ED7-EA2125902EBE");
	DECLARE_PUNK_GUID(IID_IVec4KeyFrameLinearInterpolator, "FCEC27E6-0485-461D-8750-B17BC640942A");
	DECLARE_PUNK_GUID(IID_IMat4KeyFrameLinearInterpolator, "FD05E315-21BB-4A82-8FBD-ACE3257E8A74");
	DECLARE_PUNK_GUID(IID_IQuatKeyFrameLinearInterpolator, "0D968AF8-DDC6-4FD0-954A-287F4E329941");
	DECLARE_PUNK_GUID(IID_IFloatKeyFrameLinearInterpolator, "72E39F12-59AA-41EC-B598-E184FCF00A08");

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
