#ifndef _H_IANIMATION
#define _H_IANIMATION

#include <config.h>
#include <core/iobject.h>
#include <math/vec3.h>
#include <math/quat.h>
#include "animation_track.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DEFINE_PUNK_GUID(IID_IAnimation, "3B79F2D8-3FCA-4EDC-8DE2-F51B1E4BFA84");

	class IAnimation : public virtual Core::IObject {
	public:
		virtual void AddPositionKey(int frame, Math::vec3& position) = 0;
		virtual void AddRotationKey(int frame, Math::quat& rotation) = 0;
		virtual Math::vec3& GetOrCreatePositionKey(int frame) = 0;
		virtual Math::quat& GetOrCreateRotationKey(int frame) = 0;
		virtual const Math::vec3 GetPosition(float frame) const = 0;
		virtual const Math::quat GetRotation(float frame) const = 0;
		virtual void SetPositionTrack(const AnimationTrack<Math::vec3>& track) = 0;
		virtual void SetRotationTrack(const AnimationTrack<Math::quat>& track) = 0;
		virtual const AnimationTrack<Math::vec3>& GetPositionTrack() const = 0;
		virtual const AnimationTrack<Math::quat>& GetRotationTrack() const = 0;
		virtual const Core::String& GetName() const = 0;
		virtual void SetName(const Core::String& value) = 0;
	};
}

PUNK_ENGINE_END

#endif	//	_H_IANIMATION