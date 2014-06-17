#ifndef _H_IANIMATION_PLAYER
#define _H_IANIMATION_PLAYER

#include <config.h>
#include <core/iobject.h>
#include <cstdint>
#include "ikeyframe_interpolator.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IAnimationPlayer, "81D98892-B9A8-4571-B30B-CEC355EE837E");

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

	class IAnimation;
	class IKeyFrameInterpolator;

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
		virtual void SetAnimation(IAnimation* value) = 0;
		virtual const IAnimation* GetAnimation() const = 0;
		virtual IAnimation* GetAnimation() = 0;
		virtual void SetKeyFrameInterpolator(InterpolatorType value) = 0;
		virtual InterpolatorType GetKeyFrameInterpolator() = 0;
		virtual void GetCurrentValue(std::uint32_t track_index, void* buffer, std::uint32_t size) = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_IANIMATION_PLAYER