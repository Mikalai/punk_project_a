#ifndef _H_PUNK_UTILITY_ANIMATION
#define _H_PUNK_UTILITY_ANIMATION

#include <core/object.h>
#include <math/vec3.h>
#include <math/quat.h>

#include "animation_track.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
    class PUNK_ENGINE_API Animation : public Core::Object
	{
		AnimationTrack<Math::vec3> m_pos_track;
		AnimationTrack<Math::quat> m_rot_track;
        Core::String m_name;
	public:
		Animation();
        virtual ~Animation();
		void AddPositionKey(int frame, Math::vec3& position);
		void AddRotationKey(int frame, Math::quat& rotation);
		
		Math::vec3& GetOrCreatePositionKey(int frame);
		Math::quat& GetOrCreateRotationKey(int frame);

		const Math::vec3 GetPosition(float frame) const;
		const Math::quat GetRotation(float frame) const;

		void SetPositionTrack(const AnimationTrack<Math::vec3>& track) { m_pos_track = track; }
		void SetRotationTrack(const AnimationTrack<Math::quat>& track) { m_rot_track = track; }
        const AnimationTrack<Math::vec3>& GetPositionTrack() const { return m_pos_track; }
        const AnimationTrack<Math::quat>& GetRotationTrack() const { return m_rot_track; }

        const Core::String& GetName() const;
        void SetName(const Core::String& value);        

        PUNK_OBJECT(Animation)
	};    
}
PUNK_ENGINE_END

#endif
