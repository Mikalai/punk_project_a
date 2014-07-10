#ifndef _H_IANIMATION_PLAYER
#define _H_IANIMATION_PLAYER

#include <config.h>
#include <core/action.h>
#include <core/iobject.h>
#include <cstdint>
#include "ikeyframe_interpolator.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IAnimationPlayer, "81D98892-B9A8-4571-B30B-CEC355EE837E");
	DECLARE_PUNK_GUID(CLSID_AnimationPlayer, "8EA1157A-8A93-4CE4-AF8F-1278578C39BB");

	enum class AnimationSeekDirection : std::uint32_t {
		Current,
		Begin,
		End
	};

	enum class AnimationPlaybackType : std::uint32_t {
		Once,
		Loop,
		PingPong
	};

	class IAnimated;
	class IAnimation;
	class IKeyFrameInterpolator;

	using TrackAdvanced = Core::ActionBase < std::int32_t, void*, std::uint32_t > ;
	using AnimationAdvanced = Core::ActionBase < std::int32_t > ;
	class IAnimationPlayer : public Core::IObject {
	public:
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual bool IsPlaying() const = 0;
		virtual void SetPlaybackType(AnimationPlaybackType value) = 0;
		virtual AnimationPlaybackType GetPlaybackType() const = 0;
		virtual void SetDuration(float time_s) = 0;
		virtual float GetDuration() const = 0;
		virtual void Seek(AnimationSeekDirection direction, float dt) = 0;
		virtual void SetAnimation(Core::Pointer<IAnimation> value) = 0;
		virtual const Core::Pointer<IAnimation> GetAnimation() const = 0;
		virtual Core::Pointer<IAnimation> GetAnimation() = 0;
		virtual void SetKeyFrameInterpolator(InterpolatorType value) = 0;
		virtual InterpolatorType GetKeyFrameInterpolator() = 0;
		virtual void OnAnimationStarted(Core::ActionBase<void>* action) = 0;
		virtual void OnAnimationEnded(Core::ActionBase<void>* action) = 0;
		virtual void OnFrame(AnimationAdvanced* action) = 0;
		virtual void OnFrame(std::int32_t track_index, TrackAdvanced* action) = 0;
		virtual void GetCurrentValue(std::uint32_t track_index, void* buffer, std::uint32_t size) = 0;
		/*virtual void Attach(IAnimated* value) = 0;
		virtual void Detach(IAnimated* value) = 0;*/
	};
}
PUNK_ENGINE_END

#endif	//	_H_IANIMATION_PLAYER